/*!
   \file
   \author Dane Gardner <dane.gardner@gmail.com>
   \version

   \section LICENSE
   This file is part of the Open|SpeedShop Graphical User Interface
   Copyright (C) 2010-2011 Argo Navis Technologies, LLC

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published by the
   Free Software Foundation; either version 2.1 of the License, or (at your
   option) any later version.

   This library is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
   for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this library; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

   \section DESCRIPTION

 */

#include "GraphText.h"

GraphText::GraphText(QObject *parent) :
    GraphPrimitive(parent),
    m_TextureId(0),
    m_Color(Qt::green)
{
    setFont(QFont("Helvetica"));
}

GraphText::~GraphText()
{
    if(m_TextureId) {
        glDeleteTextures(1, &m_TextureId);
        m_TextureId = 0;
    }
}

QString GraphText::text() const
{
    return m_Text;
}

void GraphText::setText(const QString &text)
{
    m_Text = text;
    if(m_TextureId) {
        init();
    }
}

QFont GraphText::font() const
{
    return m_Font;
}

void GraphText::setFont(const QFont &font)
{
    m_Font = font;
    m_Font.setPixelSize(64);

    if(m_TextureId) {
        init();
    }
}

QColor GraphText::color() const
{
    return m_Color;
}

void GraphText::setColor(const QColor &color)
{
    m_Color = color;
    if(m_TextureId) {
        init();
    }
}

QRectF GraphText::boundingBox() const
{
    QFontMetrics fontMetrics = QFontMetrics(m_Font);
    return QRectF(0, 0, fontMetrics.width(m_Text), fontMetrics.height());
}

double GraphText::height() const
{
    return 1.0;
}

double GraphText::width() const
{
    QRectF rect = boundingBox();
    double aspectRatio = rect.width() / rect.height();
    return aspectRatio;
}

void GraphText::init()
{
    // Get the size of the text according to the font
    QRectF rect = boundingBox();

    // Create the buffer and initialize it
    QPixmap pixmap(rect.size().toSize());
    pixmap.fill(Qt::transparent);

    // Create the painter, set the font and color, then draw the text
    QPainter painter(&pixmap);
    painter.setFont(m_Font);
    painter.setPen(m_Color);
    painter.drawText(painter.boundingRect(rect, m_Text), m_Text);
    painter.end();

    // Create texture
    if(m_TextureId) {
        glDeleteTextures(1, &m_TextureId);
        m_TextureId = 0;
    }

    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage convertedImage = pixmap.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied).mirrored(false, true);
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGBA, qRound(rect.width()), qRound(rect.height()), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, convertedImage.bits());

    // Create list for paint operations
    setListId(glGenLists(1));
    glNewList(listId(), GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glColor4f(m_Color.redF(), m_Color.greenF(), m_Color.blueF(), m_Color.alphaF());

    // Front side
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width(), 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width(), height(), 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, height(), 0.0f);
    glEnd();

    // Back side
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, height(), 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width(), height(), 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width(), 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEndList();
    GraphPrimitive::init();
}

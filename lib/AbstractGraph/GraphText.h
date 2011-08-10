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

#ifndef GRAPHTEXT_H
#define GRAPHTEXT_H

#include "GraphPrimitive.h"

namespace Serene {

class GraphText : public GraphPrimitive
{
    Q_OBJECT
public:
    explicit GraphText(QObject *parent = 0);
    virtual ~GraphText();

    virtual void init();

    QString text() const;
    void setText(const QString &text);

    QFont font() const;
    void setFont(const QFont &font);

    QColor color() const;
    void setColor(const QColor &color);

    double width() const;
    double height() const;

protected:
    QRectF boundingBox() const;

private:
    QString m_Text;
    QFont m_Font;
    QColor m_Color;
    GLuint m_TextureId;

};

} // namespace Serene

#endif // GRAPHTEXT_H

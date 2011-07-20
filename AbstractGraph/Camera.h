/*!
   \file
   \author Dane Gardner <dane.gardner@gmail.com>
   \version

   \section LICENSE
   This file is part of the Serene 3D Graphing Library
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

#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QtOpenGL>

class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = 0);

    /* BEGIN VIEW SETTINGS */
    void rotateAboutCenter(double pan, double tilt, double roll);
    void translateLocation(const QVector3D &translate);
    void translateCenter(const QVector3D &translate);
    void translate(const QVector3D &translate);
    double distance() const;

    const QVector3D &center() const;
    void setCenter(const QVector3D &center);
    const QVector3D &location() const;
    void setLocation(const QVector3D &location);
    const QVector3D &up() const;
    void setUp(const QVector3D &up);
    /* END VIEW SETTINGS */

    /* BEGIN PROJECTION SETTINGS */

    bool hasPerspective() const;
    void setHasPerspective(bool hasPerspective);
    double fieldOfView() const;
    void setFieldOfView(double fieldOfView);
    double nearPlane() const;
    void setNearPlane(double nearPlane);
    double farPlane() const;
    void setFarPlane(double farPlane);
    double aspectRatio() const;
    void setAspectRatio(double aspectRatio);
    /* END PROJECTION SETTINGS */

public slots:
    void refreshView();
    void refreshProjection();

signals:
    void viewChanged();
    void projectionChanged();

protected:
    const QMatrix4x4 viewMatrix();

private:
    QVector3D m_Center;
    QVector3D m_Location;
    QVector3D m_Up;

    double m_FieldOfView;
    double m_NearPlane;
    double m_FarPlane;
    double m_AspectRatio;
    bool m_HasPerspective;

};

#endif // CAMERA_H

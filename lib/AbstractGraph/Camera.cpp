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

#include "Camera.h"

namespace Serene {

Camera::Camera(QObject *parent) :
    QObject(parent),
    m_Center(0.0,0.0,0.0),
    m_Location(0.0,0.0,10.0),
    m_Up(0.0,1.0,0.0),
    m_FieldOfView(50.0),
    m_NearPlane(1.0),
    m_FarPlane(100.0),
    m_AspectRatio(4/3),
    m_HasPerspective(true)
{
    connect(this, SIGNAL(projectionChanged()), this, SLOT(refreshProjection()));
}

/* BEGIN VIEW SETTINGS */
void Camera::refreshView()
{
    glMatrixMode(GL_MODELVIEW);
    if(sizeof(qreal) == sizeof(GLdouble)) {
        glMultMatrixd((GLdouble *)viewMatrix().constData());
    } else {
        glMultMatrixf((GLfloat *)viewMatrix().constData());
    }
}

void Camera::rotateAboutCenter(double pan, double tilt, double roll)
{
    QVector3D directionVector = center() - location();
    QVector3D upVector = up();

    if(pan != 0.0) {
        QQuaternion panQuaternion = QQuaternion::fromAxisAndAngle(upVector, pan);
        directionVector = panQuaternion.rotatedVector(directionVector);
        upVector = panQuaternion.rotatedVector(upVector);
    }

    if(tilt != 0.0) {
        QQuaternion tiltQuaternion = QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(directionVector, upVector), tilt);
        directionVector = tiltQuaternion.rotatedVector(directionVector);
        upVector = tiltQuaternion.rotatedVector(upVector);
    }

    if(roll != 0.0) {
        QQuaternion rollQuaternion = QQuaternion::fromAxisAndAngle(directionVector, roll);
        directionVector = rollQuaternion.rotatedVector(directionVector);
        upVector = rollQuaternion.rotatedVector(upVector);
    }

    setUp(upVector);
    setLocation(center() - directionVector);
}

void Camera::translateCenter(const QVector3D &translate)
{
    QVector3D directionVector = center() - location();
    QVector3D upVector = up();

    QVector3D translationVector = QVector3D::normal(directionVector, upVector) * translate.x()
                                + upVector.normalized() * translate.y()
                                + directionVector.normalized() * translate.z();

    setCenter(center() + translationVector);
}

void Camera::translateLocation(const QVector3D &translate)
{
    QVector3D direction = center() - location();
    QVector3D upVector = up();

    QVector3D translationVector = QVector3D::normal(direction, upVector) * translate.x()
                                + upVector.normalized() * translate.y()
                                + direction.normalized() * translate.z();

    setLocation(location() + translationVector);
}

void Camera::translate(const QVector3D &translate)
{
    QVector3D direction = center() - location();
    QVector3D upVector = up();

    QVector3D translationVector = QVector3D::normal(direction, upVector) * translate.x()
                                + upVector.normalized() * translate.y()
                                + direction.normalized() * translate.z();

    setLocation(location() + translationVector);
    setCenter(center() + translationVector);
}


double Camera::distance() const
{
    return QVector3D(location() - center()).length();
}


const QMatrix4x4 Camera::viewMatrix()
{
    QMatrix4x4 matrix;
    matrix.lookAt(location(), center(), up());
    return matrix;
}

const QVector3D &Camera::center() const
{
    return m_Center;
}

void Camera::setCenter(const QVector3D &center)
{
    m_Center = center;

    /* In an ortho view, the projection is dependent upon the distance between the object and the view location */
    if(!hasPerspective()) {
        emit projectionChanged();
    }

    emit viewChanged();
}

const QVector3D &Camera::location() const
{
    return m_Location;
}

void Camera::setLocation(const QVector3D &location)
{
    m_Location = location;

    /* In an ortho view, the projection is dependent upon the distance between the object and the view location */
    if(!hasPerspective()) {
        emit projectionChanged();
    }

    emit viewChanged();
}

const QVector3D &Camera::up() const
{
    return m_Up;
}

void Camera::setUp(const QVector3D &up)
{
    m_Up = up;
    m_Up.normalize();
}
/* END VIEW SETTINGS */

/* BEGIN PROJECTION SETTINGS */
void Camera::refreshProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(hasPerspective()) {
        gluPerspective(fieldOfView(), aspectRatio(), nearPlane(), farPlane());
    } else {
        double y = (fieldOfView() / 90.0) * distance();
        double x = y * aspectRatio();
        glOrtho(-x, x, -y, y, nearPlane(), farPlane());
    }

    glMatrixMode(GL_MODELVIEW);
}

bool Camera::hasPerspective() const
{
    return m_HasPerspective;
}

void Camera::setHasPerspective(bool hasPerspective)
{
    m_HasPerspective = hasPerspective;
    emit projectionChanged();
}

double Camera::fieldOfView() const
{
    return m_FieldOfView;
}

void Camera::setFieldOfView(double fieldOfView)
{
    m_FieldOfView = fieldOfView;
    emit projectionChanged();
}

double Camera::nearPlane() const
{
    return m_NearPlane;
}

void Camera::setNearPlane(double nearPlane)
{
    m_NearPlane = nearPlane;
    emit projectionChanged();
}

double Camera::farPlane() const
{
    return m_FarPlane;
}

void Camera::setFarPlane(double farPlane)
{
    m_FarPlane = farPlane;
    emit projectionChanged();
}

double Camera::aspectRatio() const
{
    return m_AspectRatio;
}

void Camera::setAspectRatio(double aspectRatio)
{
    m_AspectRatio = aspectRatio;
    emit projectionChanged();
}
/* END PROJECTION SETTINGS */

} // namespace Serene

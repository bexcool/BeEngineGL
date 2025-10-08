//
// Created by Petr Pavlík on 29.09.2025.
//

#include "Transform.h"

#include "Location.h"
#include "Rotation.h"
#include "Scale.h"

#include <string>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_float.hpp>

Transform::Transform()
{
    _location = Location();
    _rotation = Rotation();
    _scale = Scale();
    _transformMatrix = glm::mat4(1.0f);
}


Transform::Transform(Location translation, Rotation rotation, Scale scale)
{
    _location = translation;
    _rotation = rotation;
    _scale = scale;

    _transformMatrix = glm::mat4(1.0f);
    _transformMatrix = glm::translate<float>(_transformMatrix,
                                             glm::vec3(_location.GetX(), _location.GetY(), _location.GetZ()));
    _transformMatrix = glm::rotate<float>(_transformMatrix, _rotation.GetRoll(), glm::vec3(1, 0, 0));
    _transformMatrix = glm::rotate<float>(_transformMatrix, _rotation.GetPitch(), glm::vec3(0, 1, 0));
    _transformMatrix = glm::rotate<float>(_transformMatrix, _rotation.GetYaw(), glm::vec3(0, 0, 1));
    _transformMatrix = glm::scale<float>(_transformMatrix, glm::vec3(_scale.GetX(), _scale.GetY(), _scale.GetZ()));
}

Transform::Transform(glm::mat4 *transformMatrix)
{
    this->_transformMatrix = (*transformMatrix);
}

glm::mat4 *Transform::AsMatrix()
{
    return &_transformMatrix;
}

Location Transform::GetLocation() const
{
    return _location;
}

void Transform::SetLocation(Location location)
{
    _location = location;
}


Rotation Transform::GetRotation() const
{
    return _rotation;
}

void Transform::SetRotation(Rotation rotation)
{
    _rotation = rotation;
}

Scale Transform::GetScale() const
{
    return _scale;
}

void Transform::SetScale(Scale scale)
{
    _scale = scale;
}

Transform Transform::operator+(const Transform &transform) const
{
    return Transform(GetLocation() + transform.GetLocation(),
                     GetRotation() + transform.GetRotation(),
                     GetScale() + transform.GetScale());
}

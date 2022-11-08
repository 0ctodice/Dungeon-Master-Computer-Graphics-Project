#pragma once

#include "glm.hpp"

namespace glimac
{
    class TrackballCamera
    {
    private:
        float m_fDistance = 5.f;
        float m_fAngleX = 0.f;
        float m_fAngleY = 0.f;

    public:
        void moveFront(float delta)
        {
            m_fDistance += delta;
        };

        void rotateLeft(float degrees)
        {
            m_fAngleY += degrees;
        }

        void rotateUp(float degrees)
        {
            m_fAngleX += degrees;
        }

        glm::mat4 getViewMatrix() const
        {
            glm::mat4 vMatrix(1.f);
            vMatrix = glm::translate(vMatrix, glm::vec3(0.f, 0.f, -m_fDistance));
            vMatrix = glm::rotate(vMatrix, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
            vMatrix = glm::rotate(vMatrix, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));

            return vMatrix;
        }
    };
}
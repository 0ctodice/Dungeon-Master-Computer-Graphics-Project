#pragma once

#include "glm.hpp"

namespace glimac
{
    class FreeflyCamera
    {
    private:
        glm::vec3 m_Position;
        float m_fPhi;
        float m_fTheta;

        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

        void computeDirectionVectors()
        {
            m_FrontVector = glm::vec3(
                glm::cos(m_fTheta) * glm::sin(m_fPhi),
                glm::sin(m_fTheta),
                glm::cos(m_fTheta) * glm::cos(m_fPhi));

            m_LeftVector = glm::vec3(
                glm::sin(m_fPhi + (glm::pi<float>() / 2.f)),
                0.f,
                glm::cos(m_fPhi + (glm::pi<float>() / 2.f)));

            m_UpVector = glm::normalize(glm::cross(m_FrontVector, m_LeftVector));
        }

    public:
        FreeflyCamera() : m_Position{glm::vec3(0)}, m_fPhi{M_PI}, m_fTheta{0.f} { computeDirectionVectors(); }
        void moveLeft(float t)
        {
            m_Position += t * m_LeftVector;
            computeDirectionVectors();
        }
        void moveFront(float t)
        {
            m_Position += t * m_FrontVector;
            computeDirectionVectors();
        }
        void rotateLeft(float degrees)
        {
            m_fPhi += glm::radians(degrees);
            computeDirectionVectors();
        }
        void rotateUp(float degrees)
        {
            m_fTheta += glm::radians(degrees);
            computeDirectionVectors();
        }
        glm::mat4 getViewMatrix() const
        {
            return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
        }
    };
}
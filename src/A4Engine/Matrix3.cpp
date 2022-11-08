#include <A4Engine/Matrix3.hpp>

Matrix3::Matrix3(const Matrix3& matrix)
{
    for (auto i = 0; i < 3; i++)
        for (auto j = 0; j < 3; j++)
            m_matrix[i][j] = matrix.m_matrix[i][j];
}

Matrix3& Matrix3::operator*(const Vector2f& value) const
{
	// TODO: insérer une instruction return ici
}

Matrix3& Matrix3::operator*(float value)
{
    Matrix3 result;

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            result.m_matrix[i][j] = value * m_matrix[i][j];

    return result;
}

Matrix3& Matrix3::operator*=(const Vector2f& value) const
{
    // TODO: insérer une instruction return ici
}

Matrix3& Matrix3::operator*=(float value)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m_matrix[i][j] *= value;
    
    return *this;
}

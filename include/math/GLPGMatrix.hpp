#pragma once
#include <array>
#include <initializer_list>

namespace GLPG {

    template <std::size_t R, std::size_t C, typename T>
        class matrix
        {
            public:
                /* TODO: The below members must be made private */
                static constexpr std::size_t rows = R;
                static constexpr std::size_t cols = C;
                static constexpr std::size_t size = C * R;

                /* Constructors */
                matrix(void);
                matrix(T val);
                matrix(std::initializer_list<T> vals);

                /* Operators */
                friend std::ostream& operator<<(std::ostream& os, const matrix& m);
                std::array<T, C> operator[](std::size_t idx) const;
                std::array<T, C>& operator[](std::size_t idx);
                void identity() {
                    for (std::size_t i = 0; i < rows; i++) {
                        for (std::size_t j = 0; j < cols; j++) {
                            values[i][j] = T(0);
                        }
                    }
                    for (std::size_t i = 0; i < rows; i++)
                        values[i][i] = T(1);
                }

                /* Getters. Useless untill the constexpr members are made private */
                inline constexpr std::size_t numRows() const;
                inline constexpr std::size_t numCols() const;
                inline constexpr std::size_t numVals() const;

                /* Storage backing
                 * TODO: Currently, the assumption is that all the
                 * values in the arrays are allocated contigiously.
                 * Verify this assumption
                 * TODO: Must be made private
                 */
                std::array<std::array<T, cols>, rows> values{};

                /* Functions */
                T* data();
        };

    template <std::size_t R, std::size_t C, typename T>
        matrix<R, C, T>::matrix()
        {
            for (std::size_t i = 0; i < rows; i++)
                values[i][i] = T(1);
        }

    template <std::size_t R, std::size_t C, typename T>
        matrix<R, C, T>::matrix(T val)
        {
            for (std::size_t i = 0; i < rows; i++)
                values[i][i] = val;
        }

    template <std::size_t R, std::size_t C, typename T>
        matrix<R, C, T>::matrix(std::initializer_list<T> vals)
        {
            std::size_t i = 0;
            std::size_t j = 0;

            for (auto val : vals) {
                values[i][j++] = val;
                //TODO: Just why?
                i = (((j == C) && !(j = 0)) ? ++i : i);
            }   
        }

    template <std::size_t R, std::size_t C, typename T>
        std::ostream& operator<<(std::ostream& os, matrix<R, C, T>& m)
        {
            os << std::endl;
            for (std::size_t i = 0; i < R; i++) {
                for (std::size_t j = 0; j < C; j++)
                    os << m.values[i][j] << " ";
                os << std::endl;
            }
            return os;
        }

    template <std::size_t R, std::size_t C, typename T>
        std::array<T, C>& matrix<R, C, T>::operator[](std::size_t idx)
        {
            return values[idx];
        }

    template <std::size_t R, std::size_t C, typename T>
        std::array<T, C> matrix<R, C, T>::operator[](std::size_t idx) const
        {
            return values[idx];
        }

    template <std::size_t R, std::size_t C, typename T>
        constexpr std::size_t matrix<R, C, T>::numRows() const
        {
            return rows;
        }

    template <std::size_t R, std::size_t C, typename T>
        constexpr std::size_t matrix<R, C, T>::numCols() const
        {
            return cols;
        }

    template <std::size_t R, std::size_t C, typename T>
        constexpr std::size_t matrix<R, C, T>::numVals() const
        {
            return size;
        }

    template <std::size_t R, std::size_t C, typename T>
        T* matrix<R, C, T>::data()
        {
            return values[0].data();
        }

    using mat4x4_i = matrix<4, 4, int>;
    using mat4x4_f = matrix<4, 4, float>;
    using mat4x4_d = matrix<4, 4, double>;
}

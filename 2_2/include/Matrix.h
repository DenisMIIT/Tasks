#pragma once

#include <cstddef>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Represents a rectangular matrix.
     * @tparam T Element type.
     */
    template <typename T>
    class Matrix
    {
    private:
        /** @brief Rows of matrix elements. */
        std::vector<std::vector<T>> data_;
        /** @brief Number of rows. */
        std::size_t rows_ = 0U;
        /** @brief Number of columns. */
        std::size_t columns_ = 0U;

    public:
        /** @brief Creates an empty matrix. */
        Matrix() = default;

        /**
         * @brief Creates a matrix with the specified dimensions and initial value.
         * @param rows Number of rows.
         * @param columns Number of columns.
         * @param value Initial element value.
         */
        Matrix(const std::size_t rows, const std::size_t columns, const T& value = T{})
            : rows_(rows), columns_(columns)
        {
            if ((rows == 0U) != (columns == 0U))
            {
                throw std::invalid_argument("Rows and columns must both be positive or zero");
            }
            if (rows > data_.max_size() ||
                (columns != 0U && rows > std::vector<T>().max_size() / columns))
            {
                throw std::length_error("Matrix is too large");
            }
            data_.assign(rows, std::vector<T>(columns, value));
        }

        /** @brief Copies the dimensions and elements of another matrix. */
        Matrix(const Matrix& other) = default;

        /** @brief Transfers the data and leaves the other matrix empty. */
        Matrix(Matrix&& other) noexcept
            : data_(std::move(other.data_)), rows_(other.rows_), columns_(other.columns_)
        {
            other.data_.clear();
            other.rows_ = 0U;
            other.columns_ = 0U;
        }

        /** @brief Replaces this matrix with a copy of another matrix. */
        Matrix& operator=(const Matrix& other)
        {
            if (this != &other)
            {
                Matrix copy(other);
                *this = std::move(copy);
            }
            return *this;
        }

        /** @brief Transfers another matrix into this matrix. */
        Matrix& operator=(Matrix&& other) noexcept
        {
            if (this != &other)
            {
                data_ = std::move(other.data_);
                rows_ = other.rows_;
                columns_ = other.columns_;
                other.data_.clear();
                other.rows_ = 0U;
                other.columns_ = 0U;
            }
            return *this;
        }

        /** @brief Releases matrix storage automatically. */
        ~Matrix() = default;

        /** @return Number of rows. */
        std::size_t rowsCount() const noexcept
        {
            return rows_;
        }

        /** @return Number of columns. */
        std::size_t columnsCount() const noexcept
        {
            return columns_;
        }

        /** @return Whether the matrix has no elements. */
        bool empty() const noexcept
        {
            return rows_ == 0U || columns_ == 0U;
        }

        /**
         * @brief Returns a row by index. Do not resize the returned row.
         * @param row Zero-based row index.
         * @return Reference to the selected row.
         */
        std::vector<T>& operator[](const std::size_t row)
        {
            return data_.at(row);
        }

        /** @brief Returns a read-only row by index. */
        const std::vector<T>& operator[](const std::size_t row) const
        {
            return data_.at(row);
        }

        /** @brief Returns an element with checked row and column indices. */
        T& at(const std::size_t row, const std::size_t column)
        {
            return data_.at(row).at(column);
        }

        /** @brief Returns a copy of an element with checked indices. */
        T at(const std::size_t row, const std::size_t column) const
        {
            return data_.at(row).at(column);
        }

        /** @brief Returns an element by its flattened, zero-based index. */
        T& flatAt(const std::size_t index)
        {
            if (columns_ == 0U)
            {
                throw std::out_of_range("Matrix index is outside its size");
            }
            return at(index / columns_, index % columns_);
        }

        /** @brief Returns a copy of an element by its flattened index. */
        T flatAt(const std::size_t index) const
        {
            if (columns_ == 0U)
            {
                throw std::out_of_range("Matrix index is outside its size");
            }
            return at(index / columns_, index % columns_);
        }

        /** @brief Compares matrix dimensions and elements. */
        bool operator==(const Matrix& other) const
        {
            return rows_ == other.rows_ && columns_ == other.columns_ && data_ == other.data_;
        }

        /** @brief Checks whether two matrices differ. */
        bool operator!=(const Matrix& other) const
        {
            return !(*this == other);
        }

        /**
         * @brief Fills all elements in row-major order.
         * @param generator Generator providing the values.
         */
        void fill(const Generator& generator)
        {
            for (std::size_t row = 0U; row < rowsCount(); ++row)
            {
                for (std::size_t column = 0U; column < columnsCount(); ++column)
                {
                    data_[row][column] = static_cast<T>(generator.generate());
                }
            }
        }

        /**
         * @brief Shifts each row left, filling vacated positions with zeros.
         * @param count Number of positions to shift.
         * @return Shifted matrix.
         */
        Matrix operator<<(const std::size_t count) const
        {
            Matrix result(rows_, columns_);
            if (count >= columns_)
            {
                return result;
            }
            for (std::size_t row = 0U; row < rows_; ++row)
            {
                for (std::size_t column = 0U; column < columns_ - count; ++column)
                {
                    result[row][column] = data_[row][column + count];
                }
            }
            return result;
        }

        /**
         * @brief Shifts each row right, filling vacated positions with zeros.
         * @param count Number of positions to shift.
         * @return Shifted matrix.
         */
        Matrix operator>>(const std::size_t count) const
        {
            Matrix result(rows_, columns_);
            for (std::size_t row = 0U; row < rows_; ++row)
            {
                for (std::size_t column = count; column < columns_; ++column)
                {
                    result[row][column] = data_[row][column - count];
                }
            }
            return result;
        }

        /** @return Matrix elements formatted as a text table. */
        std::string toString() const
        {
            std::ostringstream output;
            for (std::size_t row = 0U; row < rows_; ++row)
            {
                for (std::size_t column = 0U; column < columns_; ++column)
                {
                    if (column != 0U)
                    {
                        output << ' ';
                    }
                    output << data_[row][column];
                }
                if (row + 1U != rows_)
                {
                    output << '\n';
                }
            }
            return output.str();
        }
    };

    /** @brief Writes a matrix to an output stream. */
    template <typename T>
    std::ostream& operator<<(std::ostream& output, const Matrix<T>& matrix)
    {
        return output << matrix.toString();
    }

    /** @brief Reads a matrix, preserving its original contents on failure. */
    template <typename T>
    std::istream& operator>>(std::istream& input, Matrix<T>& matrix)
    {
        Matrix<T> result(matrix);
        for (std::size_t row = 0U; row < result.rowsCount(); ++row)
        {
            for (std::size_t column = 0U; column < result.columnsCount(); ++column)
            {
                if (!(input >> result[row][column]))
                {
                    return input;
                }
            }
        }
        matrix = std::move(result);
        return input;
    }
}

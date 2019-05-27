#ifndef MATRIX_H
#define MATRIX_H

#include <map>
#include <tuple>
#include <memory>

template<typename T> using matrix_type = std::map<std::pair<int, int>, T>;


template<typename T, T VALUE>
class Cell {
public:
    Cell(
        std::shared_ptr<matrix_type<T>> matrix,
        const int row,
        const int column): _matrix(matrix), _row(row), _column(column) {};
    Cell(const Cell& cell) {
        _row = cell._row;
        _column = cell._column;
    }
    ~Cell() = default;

    int getRow() const {
        return _row;
    }

    int getColumn() const {
        return _column;
    }

    Cell<T, VALUE>& operator =(const T& value) {
        (*_matrix.get())[std::pair<int, int>(_row, _column)] = value;
        return (*this);
    };

    bool operator == (const T& value) const {
        auto it = _matrix.get()->find(std::pair<int, int>(_row, _column));
        if (it == _matrix.get()->end()) {
            return value == VALUE;
        }
        return (*it).second == value;
    }

    friend std::ostream& operator <<(std::ostream& out, const Cell<T, VALUE>& cell) {
        auto it = cell._matrix.get()->find(std::pair<int, int>(cell._row, cell._column));
        if (it == cell._matrix.get()->end()) {
            out << VALUE;
        }
        else {
            out << (*it).second;
        }
        return out;
    };

private:
    int _row;
    int _column;
    std::shared_ptr<matrix_type<T>> _matrix;
};


template<typename T, T VALUE>
class Row {
public:
    Row(std::shared_ptr<matrix_type<T>> matrix, const int row):
        _matrix(matrix), _row(row) {};

    Row(const Row& row) {
        _matrix = row._matrix;
        _row = row._row;
    };

    ~Row() = default;

    Cell<T, VALUE> operator [](const int idx) const {
        return Cell<T, VALUE>(_matrix, _row, idx);
    };
private:
    int _row;
    std::shared_ptr<matrix_type<T>> _matrix;
};


template <typename T>
class MatrixIterator {
public:
    MatrixIterator(std::shared_ptr<matrix_type<T>> matrix, bool begin): _matrix(matrix) {
        if (begin) {
            this->_it = _matrix.get()->begin();
        }
        else {
            this->_it = _matrix.get()->end();
        }
    };

    bool operator !=(const MatrixIterator<T>& iterator) const {
        return _it != iterator._it;
    }
    
    bool operator ==(const MatrixIterator<T>& iterator) const {
        return _it == iterator._it;
    }

    std::tuple<int, int, T&> operator *() const {
        auto& idx = (*_it).first;
        auto& value = (*_it).second;
        return std::make_tuple(idx.first, idx.second, std::ref(value));
    }

    MatrixIterator<T>& operator ++() {
        _it++;
        return *this;
    }

private:
    std::shared_ptr<matrix_type<T>> _matrix;
    typename matrix_type<T>::iterator _it;
};


template <typename T, T VALUE>
class Matrix {
public:
    using value_type = Cell<T, VALUE>;
    using pointer = value_type*;
    using const_pointer = const pointer;
    using reference = value_type&;
    using const_reference = const reference;
    using iterator = MatrixIterator<T>;
    using const_iterator = MatrixIterator<const T>;

    Matrix(const Matrix<T, VALUE>& matrix) {
        _matrix = matrix._matrix;
    };

    Matrix() = default;
    ~Matrix() = default;

    int size() const {
        return _matrix.get()->size();
    };

    Row<T, VALUE> operator [](int idx) const {
        return Row<T, VALUE>(_matrix, idx);
    };

    iterator begin() {
        return iterator(_matrix, true);
    }

    iterator end() {
        return iterator(_matrix, false);
    }

    const_iterator cbegin() {
        return const_iterator(_matrix);
    }

    const_iterator cend() {
    }

private:
    std::shared_ptr<matrix_type<T>> _matrix = std::make_shared<matrix_type<T>>(matrix_type<T>());
};

#endif

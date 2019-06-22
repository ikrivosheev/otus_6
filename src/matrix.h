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
        const int column): _key(row, column), _matrix(matrix) {};
    Cell(const Cell& cell) = default;
    ~Cell() = default;

    int getRow() const {
        return _key.first();
    }

    int getColumn() const {
        return _key.second;
    }

    Cell<T, VALUE>& operator =(const T& value) {
        auto it = _matrix->find(_key);
        if (it == _matrix->end()) {
            if (value != VALUE) {
                (*_matrix)[_key] = value;
            }
        }
        else {
            if (value == VALUE) {
                _matrix->erase(it);
            }
            else {
                (*_matrix)[_key] = value;
            }
        }
        return (*this);
    };

    bool operator == (const T& value) const {
        auto it = _matrix->find(_key);
        if (it == _matrix->end()) {
            return value == VALUE;
        }
        return (*it).second == value;
    }

    friend std::ostream& operator <<(std::ostream& out, const Cell<T, VALUE>& cell) {
        auto it = cell._matrix->find(cell._key);
        if (it == cell._matrix->end()) {
            out << VALUE;
        }
        else {
            out << (*it).second;
        }
        return out;
    };

private:
    std::pair<int, int> _key;
    std::shared_ptr<matrix_type<T>> _matrix;
};


template<typename T, T VALUE>
class Row {
public:
    Row(std::shared_ptr<matrix_type<T>> matrix, const int row):
        _row(row), _matrix(matrix){};

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
    MatrixIterator(const T& it): _it(it) {};

    bool operator !=(const MatrixIterator<T>& iterator) const {
        return _it != iterator._it;
    }
    
    bool operator ==(const MatrixIterator<T>& iterator) const {
        return _it == iterator._it;
    }

    std::tuple<int, int, typename std::iterator_traits<T>::value_type::second_type&> operator *() const {
        auto& idx = (*_it).first;
        auto& value = (*_it).second;
        return std::make_tuple(idx.first, idx.second, std::ref(value));
    }

    MatrixIterator<T>& operator ++() {
        _it++;
        return *this;
    }

private:
    T _it;
};


template <typename T, T VALUE>
class Matrix {
public:
    using value_type = Cell<T, VALUE>;
    using pointer = value_type*;
    using const_pointer = const pointer;
    using reference = value_type&;
    using const_reference = const reference;
    using iterator = MatrixIterator<typename matrix_type<T>::iterator>;
    using const_iterator = MatrixIterator<typename matrix_type<T>::const_iterator>;

    Matrix(const Matrix<T, VALUE>& matrix) {
        _matrix = matrix._matrix;
    };

    Matrix() = default;
    ~Matrix() = default;

    int size() const {
        return _matrix->size();
    };

    Row<T, VALUE> operator [](int idx) const {
        return Row<T, VALUE>(_matrix, idx);
    };

    iterator begin() {
        return iterator(_matrix->begin());
    }

    iterator end() {
        return iterator(_matrix.end());
    }

    const_iterator cbegin() {
        return const_iterator(_matrix.cbegin());
    }

    const_iterator cend() {
        return const_iterator(_matrix.cend());
    }

private:
    std::shared_ptr<matrix_type<T>> _matrix = std::make_shared<matrix_type<T>>(matrix_type<T>());
};

#endif

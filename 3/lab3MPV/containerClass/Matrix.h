#pragma once

#pragma once
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <compare>
#include <memory>
#include <limits>

template<std::default_initializable T>
class Matrix;

/**
 * @brief Класс итератора для матрицы
 * @tparam T тип данных
 * @tparam is_const true - const, false - не const
 */
template<typename T, bool is_const>
class MatrixIterator {
    using elem_ptr_t =std::conditional_t<is_const, const T, T>*;///<тип указателя на элемент матрицы
    elem_ptr_t elem;///<сам указатель на эдемент
    explicit MatrixIterator(elem_ptr_t elem) : elem(elem) {};///<конструктор
    friend Matrix<T>;///<дружественный класс матрица
    friend MatrixIterator<T, !is_const>;///<его обратная версия(по константости)

public:
    using difference_type = ptrdiff_t;///<дистанция между итервторами
    using value_type = T;///< тип значения
    using element_type = std::conditional_t<is_const, const T, T>;///<тип адресуемый итератором
    using reference = std::conditional_t<is_const, const T, T>&;///<тип ссилки на хранимое значение
    using pointer = std::conditional_t<is_const, const T, T>*;///<тип указателя на хранимое значение
    using iterator_category= std::random_access_iterator_tag;///<категория итератора
    using iterator_concept = std::contiguous_iterator_tag;///тег, что итератор, является именно contiguous

    /**
     *@brief копирующий конструктор
     *@note из константнгого в неконстантный нельзя
     *@param other кого копируем
     */
    template <bool other_const>
    MatrixIterator(const MatrixIterator<T, other_const> &other) noexcept
    requires(is_const>=other_const)
    : elem(other.elem) {}

    /**
     * @brief копирующиий оператор присваиванния
     * @tparam other_const еонстантность
     * @param other копируемый итератор
     * @return указатель на тот, куда скопировали
     *  @note из константнгого в неконстантный нельзя
     */
    template <bool other_const>
    MatrixIterator& operator=(const MatrixIterator<T, other_const> &other) noexcept
    requires(is_const>=other_const){
        elem = other.elem;
        return *this;
    }

    /**
     * @brief префиксный инкремент, перемещает итератор на слуд поз
     * @return итератор
     */
    MatrixIterator& operator++() noexcept {
        ++elem;
        return *this;
    }
    /**
        * @brief постфиксный инкремент, перемещает итератор на слуд поз
        * @return копия еще не инкрементированного итератора
    */
    MatrixIterator operator++(int) noexcept {
        MatrixIterator tmp(elem);
        ++elem;
        return tmp;
    }

    /**
     * @brief обращение к полям элемента
     * @return ссылка на элемент
     */
    reference operator*() const noexcept { return *elem; }
    /**
     * @обращение к полю
     * @return указатель на элемент
     */
    pointer operator->() const noexcept { return elem; }
    /**
     * пустой конструктор
     */
    MatrixIterator() noexcept : elem(nullptr) {}

    /**
     * @brief оператор сравнения
     * @tparam other_const лругая константность
     * @param other итератор с котоым сравниваем
     * @return да или нет
     */
    template <bool other_const>
    bool operator == (const MatrixIterator<T, other_const> &other) const noexcept {
        return elem == other.elem;
    }

    /**
     * @brief префиксный декремент, передвигает итератор на предыдущую позицию
     * @return итератор
     */
    MatrixIterator& operator --() noexcept{
        --elem;
        return *this;
    }

    /**
     * @brief постфиксный декремент, передвигает итератор на предыдущую позицию
     * @return капия еще не перелвинктого итератора
     */
    MatrixIterator operator --(int) noexcept {
        MatrixIterator tmp(elem);
        --elem;
        return tmp;
    }

    /**
     * @brief спейсшип
     * @tparam other_const другая конст
     * @param other с которым сраыниваем
     * @return да нет
     */
    template <bool other_const>
    std::strong_ordering operator <=> (const MatrixIterator<T, other_const> &other) const noexcept {
        return elem <=> other.elem;
    }

    /**
     * @brief вычитание итераторов
     * @param other итератор который вычитаем
     * @return расстояние меж ними
     */
    difference_type operator - (const MatrixIterator &other) const noexcept {
        return elem - other.elem;
    }

    /**
     *
     * @param other сдвиг на какое то число
     * @return итератоа
     */
    MatrixIterator& operator +=(difference_type other) noexcept {
        elem += other;
        return *this;
    }

    /**
     * @brief сдвиг итератора на какое то число
     * @param other cldbu
     * @return его копия сдвинутая
     */
    MatrixIterator operator +(difference_type other) const noexcept {
        MatrixIterator tmp(elem);
        return (tmp += other);
    }

    /**
     *
     * @param lhs на сколко сдвигаем
     * @param rhs кого сдвигаем
     * @return копия сдвинутая
     */
    friend MatrixIterator operator + (difference_type lhs,  MatrixIterator rhs) noexcept {
        return rhs += lhs;
    }

    /**
     * @brief сдвиг итератора на какое то число назад
     * @param other сдвиг
     * @return итаратор
     */
    MatrixIterator& operator -=(difference_type other) noexcept {
        elem -= other;
        return *this;
    }

    /**
      * @brief сдвиг итератора на какое то число назад
      * @param other сдвиг
      * @return сдвинутая копия иткратора
      */
    MatrixIterator operator - (difference_type other) const noexcept {
        MatrixIterator tmp(elem);
        return tmp -= other;
    }

    /**
     * @brief индексирование
     * @param index пощиция от текщего значения итератора
     * @return ссылка на элемент, в этой позиции
     */
    reference operator[] (difference_type index) const noexcept {
        return *(elem + index);
    }



};
static_assert(std::contiguous_iterator<MatrixIterator<int, false>>);
static_assert(std::contiguous_iterator<MatrixIterator<int, true>>);

/**
 * @brief мартрица
 * @tparam T тип хранимого значения, должен иметь дефолный конструктор
 */
template<std::default_initializable T>
class Matrix {
    std::unique_ptr<T[]> data_;///<массив элементов
    size_t rows_, cols_;///<число линий, столбцов
public:
    /**
     * @конструктор, по строкам/столбцам
     * @param rows строки
     * @param cols столбцы
     */
    Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
        data_ = std::make_unique<T[]>(rows * cols);
    }

    using value_type = T;///<тип хранимого значения
    using reference = T&;///< сслыка на хранимое значение
    using const_reference = const T&;///< константная ссылка на хранимое значение
    using iterator = MatrixIterator<T, false>;///< тип итератора
    using const_iterator = MatrixIterator<T, true>;///тип конст иетратора
    using difference_type = ptrdiff_t;///< тип расстояния меж итераторами
    using size_type = size_t;///< тип размера


    Matrix() noexcept : data_(nullptr), rows_(0), cols_(0) {}///< пустой конструктоор

    /**
     * @brief копирующий конструктор
     * @param other из котороый копируем
     */
    Matrix (const Matrix &other) requires(std::default_initializable<T>) : cols_(other.cols_), rows_(other.rows_)
    {
        data_ = std::make_unique<T[]>(rows_ * cols_);
        std::copy(other.data_.get(), other.data_.get() + other.rows_ * other.cols_, data_.get());

    }

    Matrix(Matrix &&value) noexcept=default;///< перемешающмй конструктор



    ~Matrix() noexcept=default;///< деструктор
    /**
     * @brief копипрующий оператор присваивония
     * @param value отекда копируемх
     * @return указатель на нашу мптрицу
     */
    Matrix &operator=(const Matrix &value) requires(std::default_initializable<T>)
    {
        if (this != &value) {
            std::unique_ptr<T[]> tmp = std::make_unique<T[]>(rows_ * cols_);
            std::copy(value.data_.get(), value.data_.get() + value.rows_ * value.cols_, tmp.get());
            data_=std::move(tmp);
            rows_=value.rows_;
            cols_=value.cols_;
        }
        return *this;
    }

    Matrix &operator=(Matrix &&value) noexcept=default;///< перемещаюший оператор присваивания


    [[nodiscard]]bool empty() const noexcept { return rows_ == 0 || cols_ == 0; }///< проверка на пустоту
    /**
     * @кол во элементов в патрице
     * @return размер матрицы
     */
    [[nodiscard]] size_type size() const noexcept { return rows_*cols_; }
    /**
     * @brief максимально возможный размер таблицы
     * @return максимально возможный размер таблицы
     */
    [[nodiscard]]size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }
    /**
     *
     * @return ширина таблицы(кол во столбцов)
     */
    [[nodiscard]]size_type width() const noexcept {return cols_;}
    /**
     *
     * @return высота таблицы(кол во строк)
     */
    [[nodiscard]] size_type height() const noexcept {return rows_;}


    iterator begin() noexcept { return iterator(data_.get()); } ///< итератор на первый элемент
    iterator end() noexcept { return iterator(data_.get() + rows_*cols_); } ///< итератор за последним элементом
    const_iterator end() const noexcept { return const_iterator(data_.get() + rows_*cols_); } ///< константный итератор на первый элемент для константой таблицы
    const_iterator begin() const noexcept { return const_iterator(data_.get()); }///< константный итератор за последним элементом для контантной таблицы
    const_iterator cbegin() const noexcept { return const_iterator(data_.get());}///< константный итератор на первый элемент
    const_iterator cend() const noexcept { return const_iterator(data_.get() + rows_*cols_); }///< константный итератор за последним элементом

    //get
    /**
     * @brief индексирование [нужная строка][нужный столбец]
     * @param row  строка
     * @return элемент по адруссе
     */
    T *operator [](const size_t row) {return data_.get()+row*cols_;}
    /**
     * @brief клнстанстное индексирование [нужная строка][нужный столбец]
     * @param row  строка
     * @return элемент по адрессу
     */
    const T *operator [](const size_t row) const{return data_.get()+row*cols_;}

    /**
     * @brief метод для свапа матриц
     * @param other с чем меняем местами
     */
    void swap(Matrix &other) noexcept(std::is_nothrow_constructible<T>::value && std::is_nothrow_move_assignable<T>::value) {
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(data_, other.data_);
    }

    /**
     *
     * @param first первый для свапа
     * @param second вьлолй для свапа
     */
    friend void swap(Matrix &first, Matrix &second) noexcept {
        first.swap(second);
    }

    //initialization
    /**
     *
     * @param rows кол во строк
     * @param cols кол во столюцов
     * @param list список, которым инициализируем
     */
    Matrix(size_t rows, size_t cols, std::initializer_list<T> list) : rows_(rows), cols_(cols) {
        if (list.size() != rows * cols) {
            throw std::invalid_argument("invalid size");
        }
        data_ = std::make_unique<T[]>(rows * cols);
        std::copy(list.begin(), list.end(), data_.get());
    }

    /**
     * @brief инициализация матрицы дефолтными значениями
     * @param rows кол во столбцов
     * @param cols кол во строк
     */
    Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        data_ = std::make_unique<T[]>(rows * cols);
        std::fill(data_.get(), data_.get() + rows_*cols_, T{});
    }

    /**
     * @brief перевыделение памяти
     * @param newRows кол во новыx строк
     * @param newCols кол во новыx столбцы
     */
    void resize(size_t newRows, size_t newCols) requires(std::default_initializable<T>) {
        if (rows_ > newRows || cols_ > newCols) throw std::invalid_argument("old > new");
        if (rows_ == newRows && cols_ == newCols) {return;}

        std::unique_ptr<T[]> tmp = std::make_unique<T[]>(newRows * newCols);
        std::fill(tmp.get(), tmp.get() + newRows * newCols, T{});
        for (size_t i = 0; i < rows_; i++) {
            T* srcRowStrat = data_.get() + i * cols_;
            T* destRowStart = tmp.get() + i * newCols;
            std::copy(srcRowStrat, srcRowStrat + cols_, destRowStart);
        }
        data_ = std::move(tmp);
        cols_ = newCols;
        rows_ = newRows;
    }

    /**
     *
     * @tparam Iter проверка,что это хотя бы инпут итератор
     * @param rows кол во строк
     * @param cols кол во столбцов
     * @param begin итераторо= на начло памяти, откуда копируем
     * @param end итнератор на конец памяти, откуда копируем
     */
    template<std::input_iterator Iter>
    Matrix(size_t rows, size_t cols, Iter begin, Iter end) requires(std::constructible_from<T, std::iter_reference_t<Iter>>) : rows_(rows), cols_(cols) {
        if constexpr (std::sized_sentinel_for<Iter, Iter>) {
            size_t len = std::distance(begin, end);
            if (len != rows * cols) throw std::invalid_argument("Iter range dont match with size");


        }
        data_ = std::make_unique<T[]>(rows * cols);
        std::copy(begin, end, data_.get());
    }

    /**
     *
     * @return указатель на область в памяти где наши данные
     */
    T* data() noexcept { return data_.get(); }
    const T* data() const noexcept { return data_.get(); }


    /**
     *  @brief сравненме даух матриц, равгы или нет
     * @param other с кем сравниваем
     * @return да нет
     */
    bool operator==(const Matrix &other) const noexcept {
        return (size()==other.size()) && std::equal(begin(), end(), other.begin(), other.end());
    }
};






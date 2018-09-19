#ifndef CSLIB_DATA_STRUCTURE_TENSOR_HPP
#define CSLIB_DATA_STRUCTURE_TENSOR_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <numeric>

namespace cslib {
namespace data_structure
{
    /* Class representing tensor object.
     * TODO: 
     *  -broadcasting
     *  -range cutting
     *  -linear algebra operations
     *  -dimension operations (expand, reshape, ...)
     */
    

    template <typename T>
    class Tensor
    {
    public:
        using SizeType   = size_t;
        using Dimensions = std::vector<SizeType>;
        using Strides    = std::vector<SizeType>;

    private:
        T*          _data;
        SizeType    _number_elements;
        Dimensions  _dims;
        Strides     _strides;
        bool        _is_shallow_copy;

    public:
        // Constructors
        Tensor(const Dimensions& dims) :
            _is_shallow_copy(false),
            _data(nullptr),
            _dims(dims)
        {
            auto dims_size = _dims.size();
            _strides = Strides(dims_size);

            _strides[dims_size-1] = 1;
            for (auto i = 1; i < dims_size; i++)
                _strides[i-1] = std::accumulate(_dims.begin() + i, _dims.end(), 1, std::multiplies<SizeType>());

            _number_elements = std::accumulate(_dims.begin(), _dims.end(), 1, std::multiplies<SizeType>());
            _data = new T[_number_elements];
        }

        Tensor(const Tensor& rhs)
        {
            dataRelease();

            _data = rhs._data;
            _dims = rhs._dims;
            _strides = rhs._strides;
            _number_elements = rhs._number_elements;
            _is_shallow_copy = true;
        }

        Tensor(Tensor&& rhs) noexcept
        {
            dataRelease();

            _data = rhs._data;
            _dims = rhs._dims;
            _strides = rhs._strides;
            _number_elements = rhs._number_elements;
            _is_shallow_copy = rhs._is_shallow_copy;

            rhs._data = nullptr;
            rhs._dims.clear();
            rhs._strides.clear();
            rhs._number_elements = 0;
            rhs._is_shallow_copy = false;
        }

        // Destructor
        ~Tensor() noexcept
        {
            dataRelease();
        }

        // Operators overloading
        Tensor& operator=(const Tensor& rhs)
        {
            // if (_is_shallow_copy && _is_sub_tensor) // copying sub tensor
            // {
            //     // assert (_dims == rhs._dims)?
            //     if (_dims == rhs._dims)
            //         for (auto i = 0; i < _number_elements; i++)
            //             _data[i] = rhs._data[i];
            // }
            // else // tensor is not sub tensor
            // {
            //     dataRelease();

            //     _data = rhs._data;
            //     _number_elements = rhs._number_elements;
            //     _dims = rhs._dims;
            //     _is_shallow_copy = true;
            // }

            return *this;
        }

        Tensor& operator=(Tensor&& rhs) noexcept
        {
            // if (_is_shallow_copy && _is_sub_tensor) // copying sub tensor
            // {
            //     // assert (_dims == rhs._dims)?
            //     if (_dims == rhs._dims)
            //         for (auto i = 0; i < _number_elements; i++)
            //             _data[i] = rhs._data[i];
            // }
            // else // tensor is not sub tensor
            // {
            //     dataRelease();

            //     _data = rhs._data;
            //     _number_elements = rhs._number_elements;
            //     _dims = rhs._dims;
            //     _is_shallow_copy = true;
            // }

            rhs._data = nullptr;
            rhs._number_elements = 0;
            rhs._dims.clear();
            rhs._strides.clear();
            rhs._is_shallow_copy = false;

            return *this;
        }

        Tensor& operator=(T value)
        {
            // for (auto i = 0; i < _number_elements; i++)
            //     _data[i] = value;

            return *this;
        }

        Tensor operator+(T value) const
        {
            Tensor result = make_copy();

            // for (auto i = 0; i < _number_elements; i++)
            //     result._data[i] = _data[i] + value;

            return result;
        }

        Tensor operator+(const Tensor& rhs) const
        {
            Tensor result = make_copy();

            // if (rhs._dims == _dims) // element-wise addition
            // {
            //     for (auto i = 0; i < _number_elements; i++)
            //         result._data[i] = _data[i] + rhs._data[i];
            // }

            return result;
        }

        Tensor operator*(T value) const
        {
            Tensor result = make_copy();

            // for (auto i = 0; i < _number_elements; i++)
            //     result._data[i] = _data[i] * value;

            return result;
        }

        Tensor operator*(const Tensor& rhs) const
        {
            Tensor result = make_copy();

            // if (rhs._dims == _dims) // element-wise multiply
            // {
            //     for (auto i = 0; i < _number_elements; i++)
            //         result._data[i] = _data[i] * rhs._data[i];
            // }

            return result;
        }

        Tensor operator[](int index)
        {
            auto data_offset = _data;
            Strides new_strides;
            Dimensions new_dims;
            if (_dims.size() == 1)
            {
                new_dims = Dimensions({1});
                new_strides = Strides({1});
                data_offset += i * _strides.back()
            }
            else
            {
                new_dims = Dimensions(_dims.begin() + 1, _dims.end());
                new_strides = Strides(_strides.begin() + 1, _strides.end());
                data_offset += i * _strides.front();
            }

            return Tensor(new_dims, new_strides, data_offset);
        }

        // const Tensor operator[](int index) const
        // {
        //     auto new_dimensions = _dims;
        //     new_dimensions.erase(new_dimensions.begin());

        //     if (new_dimensions.size() == 0)
        //         new_dimensions.push_back(1);

        //     auto data_offset = _data + index * std::accumulate(new_dimensions.begin(), new_dimensions.end(), 1, std::multiplies<SizeType>());
        //     return Tensor(new_dimensions, data_offset);
        // }

        // deep copy operations
        Tensor make_copy() const
        {
            auto copied_tensor = Tensor(_dims);

            for (auto i = 0; i < _number_elements; i++)
                copied_tensor._data[i] = _data[i];

            return copied_tensor;
        }

        // get properties
        const Dimensions& shape()   const  { return _dims; }
        const Strides&    strides() const  { return _strides; }
        const SizeType    size()    const  { return _number_elements; }

        // Linear algebra
        void transpose() 
        {
            // auto tmp = _dims[0];
            // _dims[0] = _dims[1];
            // _dims[1] = tmp;

            // in-place sort or some iterators magic requiered
        }

        // String representation
        std::string to_string() const
        {
            std::string result = "";
            auto num_dims = _dims.size();

            if (num_dims > 2)
            {
                for (auto i = 0; i < _dims[0]; i++)
                    result += (*this)[i].to_string();
            }
            else if (num_dims == 2)
            {
                auto _h = _dims[0];
                auto _w = _dims[1];

                result += "[";
                for (auto i = 0; i < _number_elements; i += _w)
                {
                    if (i != 0)
                        result += " [";
                    else
                        result += "[";

                    for (auto j = 0; j < _w; j++)
                    {
                        if (j != (_w - 1))
                            result += std::to_string(_data[i+j]) + ", ";
                        else
                            result += std::to_string(_data[i+j]);
                    }
                    result += "]";

                    if (i != (_h - 1))
                        result += "\n";
                }
                result += "]\n\n";
            }
            else
            {
                result += "[";
                for (auto i = 0; i < _dims[0]; i++)
                {
                    if (i != (_dims[0] - 1))
                        result += std::to_string(_data[i]) + ", ";
                    else
                        result += std::to_string(_data[i]);
                }
                result += "]  ";
            }

            return result.substr(0, result.length() - 2);
        }

    private:
        // sub-tensor ctor
        Tensor(const Dimensions& dims, const Strides& strides, const T* data_start_address)
            : _is_shallow_copy(true),
            _data(data_start_address),
            _strides(strides),
            _dims(dims)
        {
            _number_elements = std::accumulate(_dims.begin(), _dims.end(), 1, std::multiplies<SizeType>());
        }

        // Memory management
        void dataRelease()
        {
            if (!_is_shallow_copy && _data)
            {
                delete[] _data;
                _data = nullptr;
            }
        }

        // iterate engine
        void elementWiseOperation()
    };

}}

#endif // CSLIB_DATA_STRUCTURE_TENSOR_HPP

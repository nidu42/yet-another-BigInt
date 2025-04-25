// C++ 23 required!
// Just a small project by Sharapudin Dibirov aka nidu
// Let's make 'em Big Ints nice in C++!

class BigInt {
private:
    static constexpr size_t _reserve_value{ 256 };
    static constexpr int _base{ 1000000 };
    static constexpr std::string_view format_str{ "{:06}" };
    std::vector<int> _num{}; // number is written in backwards
    int _sign{};

    // private methods:

    void _reserve_optimization(std::vector<int>& vec, const std::vector<size_t>& sizes);

    void _reserve_optimization(const std::vector<size_t>& sizes);

    void _reserve_optimization();

    void _delete_leading_zeros(std::vector<int>& vec);

    void _delete_leading_zeros();

    void _init();

public:

    // Constructors and Destructor here:

    BigInt();

    BigInt(const BigInt& other);

    BigInt(BigInt&& other) noexcept;

    BigInt(const std::vector<int>& vec, int sign);

    BigInt(std::vector<int>&& vec, int sign) noexcept;

    BigInt(std::integral auto number);

    ~BigInt();

    // bunch of methods here

    int sign() const;

    size_t size() const;

    std::string to_string() const;

    void print_inner_representation() const;

    void print() const;

    void println() const;
    // bunch of operators here:

    BigInt& operator=(const BigInt& other);
    BigInt& operator=(BigInt&& other) noexcept;

    friend bool operator==(const BigInt& N1, const BigInt& N2);
    friend bool operator!=(const BigInt& N1, const BigInt& N2);
    friend bool operator<(const BigInt& N1, const BigInt& N2);
    friend bool operator>(const BigInt& N1, const BigInt& N2);
    friend bool operator<=(const BigInt& N1, const BigInt& N2);
    friend bool operator>=(const BigInt& N1, const BigInt& N2);

    friend BigInt operator+(const BigInt& N);
    friend BigInt operator-(const BigInt& N);
    friend BigInt operator+(const BigInt& N1, const BigInt& N2);
    friend BigInt operator-(const BigInt& N1, const BigInt& N2);

    // to be added: operators(*, /, %, ++, --), methods: to_string(), constructors: BigInt(std::string number), pow(BigInt N, int n), pow_mod(BigInt N, int n, BigInt mod)
};

// other functions:
namespace std {
    const BigInt abs(const BigInt& N);
    std::string to_string();
}

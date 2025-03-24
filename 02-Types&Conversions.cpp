/*******************
    TYPE CASTING
*******************/

// The process of converting a value from one type to another type is called type conversion.
// Type conversion involves a copy of the original variable being made, then changing the copy.
// Some conversions are completely safe, while others may result in loss of information.
// When the compiler does type conversion without us explicitly asking, we call this implicit conversion.
// An example is converting an int to a float. The compiler will automatically convert "1" to "1.0".

int var1 = 1;
float var2 = var1;	// See, no error

// An explicit conversion is when we tell the compiler to convert a variable type.
// This is called type casting. It can be done in two main ways, like this:

int var3 = (int)var2;   // C-style cast
int var4 = static_cast<int>(var2);  // Static cast

// There is no difference between the two except that the C-style cast may cause a compiler warning.

/***************************
    TYPES OF CONVERSIONS
***************************/

/* The conversion rules for fundamental data types are called the standard conversions, of which there
   are 4 categories. */

// NOTE: The number of bits a data type uses is called its width.
// A wider data type uses more bits, and a narrower one uses less.

// 1. NUMERIC PROMOTION
// A numeric promotion is when a narrower value gets converted to a wider value.
// There are two types of numeric promotions: Integral and floating point.
// All numeric promotions are value-preserving.

// 2. NUMERIC CONVERSION
// Unlike numeric promotions, many numeric conversions are unsafe (loss of information).
// There are 3 general safety categories:
// Value-preserving: No loss of information. (short --> double)
/* Reinterpretive: The converted value may be different than the source value, but no data is lost.
   (signed int --> unsigned int) */
// Lossy: Unsafe numeric conversions where data may be lost. (double --> float)

// 3. NARROWING CONVERSION
/* A narrowing conversion is a potentially unsafe numeric conversion where the destination type may not
   be able to hold all the values of the source type.*/
// Implicit conversions will most likely result in compiler warnings.
// This is why it's best to use static_cast<> when performing narrowing conversions.

// 4. ARITHMETIC CONVERSIONS
/* An arithmetic conversion happens when using an arithmetic operator (+, -, *, /, %) on two operands
   of different types. */
// One operand gets converted to the type of the other operand.
/* The rank of types from lowest priority to highest is: int --> long --> long long --> float -->
   double --> long double */

/*******************
    TYPE ALIASES
*******************/

// The "using" keyword can be used to make a type alias, like this:

using Distance = int;
Distance inch = 1;  // inch has type "int"

// Type aliases are not distinct types. They are simply another name for an existing type.
// A common naming convention is to put _t at the end to signify that the identifier is a type.
// The "typedef" keyword is an older way of creating a type alias. The syntax is as such:

typedef int Mass_t;
Mass_t ounce = 1;

// Both methods of creating type alises are identical.
// A good use of type aliases is to ensure a variable type has a certain number of bits, like this:

#ifdef INT_2_BYTES  // Can be #defined as a compiler/preprocessor setting
using int8_t = char;
using int16_t = int;
using int32_t = long;
#else
using int8_t = char;
using int16_t = short;
using int32_t = int;
#endif
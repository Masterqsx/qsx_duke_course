Mini-Project Option: Numerical Methods
======================================

For this option, you will be using some numerical methods
to integrate and optimize functions.

Step 1:  Parsing functions
 You will write a program "numerics" which takes one command line argument,
 which specifies the name of a file to read commands from.  To start
 with there are two commands: define and evaluate, which look like this:
  define  (f x y z) = (+ (* x y) (- z 3))
  evaluate (f 3 4.2 5)
  evaluate (f -1 9.2 6)
 For this input, your program should print
  defined  (f x y z)
  (f 3 4.2 5) = 14.6
  (f -1 9.2 6) = -6.2

  Specifically, define must be followed by (id id ...)  (that is, parenthesis
  containing one or more "id"s---which are the parameters
  to this function), where "id" is short for identifier, and
  for these purposes, an identifier is any combination of characters other
  than whitespace or numbers.  All of the following are valid identifiers:
   hello
   f
   +
   +-@#$
   x-y!!

  Next must be an = sign, followed by an expression.  An expression is
  either (id expression ...) [that is, an id followed by one or more expressions],
  OR an id by itself, or a numeric constant.  The following are all valid expressions:
    (+ 3 (* x y))
    (f x y zqweq (g (*7 n) 3))
    x
    -4.2
    23
  All function names (the first identifier in the parenthesis) must refer
  to a previously defined function, and all other identifiers must refer to parameters
  to this function.  It is an error to attempt to re-define a function which
  is already defined.

  Evaluate commands must have an expression with no variables---they may refer
  to functions, and have numeric constants for the parameters.  However, the
  may call other functions.  The following are all valid (assuming appropriate
  definitions of f, g, and h exist):
    (f 3 4.2 5)
    (f (g 1 2) (g 3 4) (h 5 6 7))

 You should make the following function names pre-defined: +, -, *, /, pow
 sqrt. 

Step 2: Numerical Integration

  The next step is to add support for numerical integration, using the
  midpoint-rectangle method.  Recall from calculus that the definite
  integral of a function is the area under its curve within certain
  bounds.  One way to approximate this integral is to compute the area
  of many narrow rectangles (each of whose height is the value of the
  function at the midpoint of the rectangle) , and sum their areas.
  With sufficiently small rectangles, the approximation of the actual
  area is quite good.  This principle generalizes to multiple
  dimensions, where the integral computes the volume under a function
  of 2 parameters (using the sum of volumes of rectangular prisms),
  and higher dimensional analogs for functions of more parameters.  

  To add this feature, your will add support for a new command "numint"
  (short for "numerical integration").
  The number of arguments that the numint command takes depends on
  the number of parameters which the function it is integrating requires.

   1. The first argument will always be the name of a defined function
   2. The second argument will be the "stepsize" (that is the width of
      each rectangle).
   3. The remaining arguments come in pairs, specifying the range of
      integration for each parameter.  There must be one range (pair
      of numbers) for each parameter.

   define  (f x y) = (+ (* 2 x) y)
   numint f 0.001 -1 1 4 5

   This would compute the volume under the curve of f(x,y) = 2*x + y
   with x ranging from -1 to 1, and y ranging from 4 to 5.   It would
   compute this by summing the volumes of 2,000,000 rectangular prisms,
   each of which has length 0.001, and width 0.001, and a height
   based on the value of f at the center of that particular rectangle.

  See AOP 10.11

Step 3: Monte Carlo Integration
  The third step is to add support for the "mcint" (Monte Carlo Integration) command.
  This command approximates the area (or volume, etc...) under a curve, but instead
  of summing the volumes of many rectangles, it uses a Monte Carlo approach.
  In particular, it picks many random points within the bounds of the integration
  range.  It then tests if each point is the value of the randomly chosen
  point is above or below the curve.

  If the curve is always non-negative in the range of integration, the
  approximation of the area is

        number of points under the curve
        --------------------------------   * total area of integration range
        total number of points chosen

  If the curve takes both positive and negative values in this range, you must
  compute subtract the number of points which land above the curve in negative
  regions (that is, above the curve, but below 0):

   positive and under - negative and above  
    ------------------------------------   * total area of integration range
      total number of points chosen


  The arguments to "mcint" are the same as "numint" except that the second
  argument is the number of trials (the number of random points to pick) instead
  of the step size.  The first parameter is still the function name, and the
  remaining parmaters are still the ranges to integrate over.
 

Step 4: Gradient Ascent
 Your final task is  to add commands which find the maximum  (the "max"
 command) or minimum (the "min" command) by gradient ascent or descent.
 See AOP questions 10.12 and 10.13 for a description of 2-D gradients,
 ascent, and descent.

The commands should take the following arguments:
  1. The name of the function
  2. gamma (as described in AoP Q 10.13)
  3. convergedDistance (again, in AoP Q 10.13)
  4. The start point, which will have as many numbers as the function has
     parameters.

      
      

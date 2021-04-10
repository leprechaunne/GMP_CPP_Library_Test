#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string>
#include <stdlib.h>

using namespace std;



//get the number of digits of an integer, excluding sign
int get_integer_length(long num) {
  //get abs to prep num
  if (num < 0)
    num *= -1;

  //base case for one digit long
  if (num < 10)
    return 1;
  
  //iteratively take a digit off until its within range
  int length = 1;
  
  while(num >= 10) {
    num /= 10;
    ++length;
  }

  return length;
} 


//concat a number num to itself k times (123, 1 ==> 123123)
//returns a s
void concat_num(mpz_t &num, int k=1) {
  int num_length = get_integer_length(mpz_get_si(num));

  mpz_t result;
  mpz_init(result);
  mpz_init_set(result, num);

  for(int i=0; i<k; ++i) {
    mpz_mul_ui(result, result, pow(10,num_length));
    mpz_add(result, result, num);
  }

  mpz_set(num, result);
  return;
}

void run_tests() {
  const char *TESTING_HEADER = "\nTesting: %-30s\n-----------------------------------\n";
  printf(TESTING_HEADER, "get_integer_length()");
  printf("Length of 0 is %-10d\n", get_integer_length(0));
  printf("Length of 69 is %-10d\n", get_integer_length(69));
  printf("Length of 420 is %-10d\n", get_integer_length(420));
  printf("Length of 1337 is %-10d\n", get_integer_length(1337));

  printf(TESTING_HEADER, "concat_num()");
  printf("xxx * xx ==> 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n");
  mpz_t tester;
  mpz_init(tester);
  for (int i=0; i<5; ++i) { 
    mpz_set_si(tester, 123);
    concat_num(tester, i);
    printf("123 * %2d ==> %-10s\n", i, mpz_get_str(NULL, 10, tester));

  }
  mpz_init(tester);
  for (int i=10; i<15; ++i) { 
    mpz_set_si(tester, 987);
    concat_num(tester, i);
    printf("987 * %2d ==> %-10s\n", i, mpz_get_str(NULL, 10, tester));

  }
  //prevent leak
  mpz_clear(tester);

}


//main
//-------------------------------------------------------


int main(int argc, char **argv){

  if (argc > 1)
    if (*argv[1] == 't'){
          run_tests();
    }

  //lets get down to business
  mpz_t numerator_int, denominator_int;
  mpz_inits(numerator_int, denominator_int, NULL);

  //
  mpq_t numerator_rational, denominator_rational, answer_rational;
  mpq_inits(numerator_rational, denominator_rational, answer_rational, NULL);

  mpf_t answer_floating;
  mpf_init2(answer_floating, 800);

  for(int i=4; i>-1; --i){
    mpz_set_si(numerator_int, 967);
    mpz_set_si(denominator_int, 123);

    concat_num(numerator_int, i);
    concat_num(denominator_int, i);

    mpq_set_d(numerator_rational, mpz_get_d(numerator_int));
    mpq_set_d(denominator_rational, mpz_get_d(denominator_int));

    mpq_div(answer_rational, numerator_rational, denominator_rational);

    mpf_set_q(answer_floating, answer_rational);

    gmp_printf("%15Zd/%15Zd = \n%.100Ff\n\n", numerator_int, denominator_int, answer_floating); 
    // gmp_printf("%.100Ff\n", answer_floating); 

  }

  //char inputStr[1024];
  /*
     mpz_t is the type defined for GMP integers.
     It is a pointer to the internals of the GMP integer data structure
   */
  // mpz_t n;
  // int flag;

  // printf ("Enter your number: ");
  // scanf("%1023s" , inputStr); /* NOTE: never every write a call scanf ("%s", inputStr);
  //                                 You are leaving a security hole in your code. */

  // /* 1. Initialize the number */
  // mpz_init(n);
  // mpz_set_ui(n,0);

  // /* 2. Parse the input string as a base 10 number */
  // flag = mpz_set_str(n,inputStr, 10);
  // assert (flag == 0); /* If flag is not 0 then the operation failed */

  //  Print n 
  // printf ("n = ");
  // mpz_out_str(stdout,10,n);
  // printf ("\n");

  // /* 3. Add one to the number */

  // mpz_add_ui(n,n,1); /* n = n + 1 */

  // /* 4. Print the result */

  // printf (" n +1 = ");
  // mpz_out_str(stdout,10,n);
  // printf ("\n");


  // /* 5. Square n+1 */

  // mpz_mul(n,n,n); /* n = n * n */


  // printf (" (n +1)^2 = ");
  // mpz_out_str(stdout,10,n);
  // printf ("\n");


  // /* 6. Clean up the mpz_t handles or else we will leak memory */
  // mpz_clear(n);

  return 0;
}



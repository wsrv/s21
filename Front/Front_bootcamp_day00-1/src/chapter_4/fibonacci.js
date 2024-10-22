// Напишите функицю, которая принимает индекс числа из ряда Фибоначчи и
// возвращает его значение. Предположим, что ряд Фибоначчи начинается с 0
// индекса.

function fibo(index) {

  if (index == 0 || index == 1)
    return 1;
  else
    return (fibo(index - 1) + fibo(index - 2))
}

console.log(fibo(5));  // Вернет 8
console.log(fibo(1));  //	1
console.log(fibo(8));  //	34
console.log(fibo(21)); //	17711
//Напишите функцию counter, которая при каждом вызове будет возвращать числа на
// 3 больше, чем в прошлый. Нельзя использовать переменные, объявленные через
// var!

// function counter() {}

function counter() {

  if (!counter.currentValue) {
    counter.currentValue = 0;
  }
  counter.currentValue += 3;

  return counter.currentValue - 3;
}

console.log(counter()); // Функция вернет 0
console.log(counter()); // Функция вернет 3
console.log(counter()); // Функция вернет 6
console.log(counter()); // Функция вернет 9

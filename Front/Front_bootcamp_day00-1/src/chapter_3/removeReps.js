// Вам нужно написать функцию которая принимает в качестве аргумента массив
// чисел и удаляет все повторяющиеся значения.

function removeReps(array) {
  result = [];
  for (let i = 0; i < array.length; i++) {
    let j = 0;
    while ((array[i] != result[j]) && (j < result.length))
      j++;
    if (j == result.length)
      result.push(array[i]);
  }
  return result;
}

console.log(
    removeReps([ 1, 1, 2, 4, 5, 6, 6, 8, 9, 11 ])); // [1,2,4,5,6,8,9,11]

console.log(removeReps([ 1, 1, 1, 1 ])); // [1]

console.log(removeReps([ 1, 2, 3, 4, 5, 6 ])); //	[1,2,3,4,5,6]
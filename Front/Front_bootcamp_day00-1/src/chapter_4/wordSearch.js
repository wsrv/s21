//  В этой задаче нужно будет написать алгоритм поиска, который скажет, можно ли
//  найти входное слово в головоломке поиска слов, которая тоже подается функции
//  на вход.
// Данная задача имеет два уровня сложности :
// - Первый уровень включает в себя исключительно поиск по вертикали и по
// горизонтали
// - Второй уровень дополнительно включает в себя поиск по диагонали
// - Слова могут быть записаны слева направо и наоборот.

function searchSubString(puzzle, word) {
  const wordLength = word.length;
  let J = puzzle.length;
  let I = puzzle[0].length;

  // Проверка строк
  for (let i = 0; i < J; i++) {
    const row = puzzle[i].join('');

    if (row.includes(word))
      return true;
    if (row.split('').reverse().join('').includes(word))
      return true;
  }
  // Проверка столбцов
  for (let i = 0; i < I; i++) {
    let column = '';

    for (let j = 0; j < J; j++)
      column += puzzle[j][i];

    if (column.includes(word))
      return true;
    if (column.split('').reverse().join('').includes(word))
      return true;
  }
  // Поиск по диагоналям
  for (let i = 0; i < J; i++) {
    for (let j = 0; j < I; j++) {
      if (puzzle[i][j] === word[0]) {
        // Поиск по диагонали вправо вниз
        let found = true;
        for (let k = 1; k < word.length; k++) {
          if (i + k >= J || j + k >= I || puzzle[i + k][j + k] !== word[k]) {
            found = false;
            break;
          }
        }
        if (found)
          return true;
        // Поиск по диагонали влево вниз
        found = true;
        for (let k = 1; k < word.length; k++) {
          if (i + k >= J || j - k < 0 || puzzle[i + k][j - k] !== word[k]) {
            found = false;
            break;
          }
        }
        if (found)
          return true;
        // Поиск по диагонали влево вверх
        found = true;
        for (let k = 1; k < word.length; k++) {
          if (i - k < 0 || j - k < 0 || puzzle[i - k][j - k] !== word[k]) {
            found = false;
            break;
          }
        }
        if (found)
          return true;
        // Поиск по диагонали вправо вверх
        found = true;
        for (let k = 1; k < word.length; k++) {
          if (i - k < 0 || j + k >= I || puzzle[i - k][j + k] !== word[k]) {
            found = false;
            break;
          }
        }
        if (found)
          return true;
      }
    }
  }

  return false;
}

const examplePuzzle = [
  [ "b", "l", "g", "o", "l", "d", "s" ],
  [ "x", "k", "q", "w", "i", "j", "p" ],
  [ "a", "n", "w", "k", "k", "p", "n" ],
  [ "h", "e", "e", "e", "k", "i", "l" ],
  [ "q", "e", "k", "a", "y", "q", "a" ],
  [ "h", "u", "h", "a", "e", "a", "u" ],
  [ "z", "q", "j", "c", "c", "m", "r" ],
];

// Level 1
console.log(searchSubString(examplePuzzle, "like"));  // true
console.log(searchSubString(examplePuzzle, "gold"));  // true
console.log(searchSubString(examplePuzzle, "queen")); // true

// // Level 2
console.log(searchSubString(examplePuzzle, "cake")); // true

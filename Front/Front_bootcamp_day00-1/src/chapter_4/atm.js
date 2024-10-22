// Напишите функцию банкомат которая принимает на вход число и возвращает объект
// в формате: {номинал_купюры : количество_купюр}. Если банкомат не может выдать
// данную сумму, то выводится ошибка 'Incorrect value'. Купюры должны выдаться
// оптимальным образом (вместо 5 купюр номиналом 1000 выдается одна 5000). За
// раз банкомат может выдавать не более 20 купюр, если купюр для выдачи не
// хватает то выводится ошибка 'Limit exceeded'

function atm(sum) {
  const banknotes = [ 5000, 2000, 1000, 500, 200, 100, 50 ];
  if (sum % 50 !== 0)
    return 'Incorrect value';

  let result = {};
  let totalBanknotes = 0;

  for (let i = 0; i < banknotes.length && sum > 0 && totalBanknotes <= 20;
       i++) {
    if (sum >= banknotes[i]) {
      result[banknotes[i]] = Math.floor(sum / banknotes[i]);
      sum -= result[banknotes[i]] * banknotes[i];
      totalBanknotes += result[banknotes[i]];
    }
  }

  if (totalBanknotes >= 20) {
    return 'Limit exceeded';
  }

  return result;

  // const sortedResult = Object.fromEntries(
  //     Object.entries(result).sort(([key1], [key2]) => parseInt(key2) -
  //     parseInt(key1))
  //   );
  //   return sortedResult;
}

console.log(
    atm(8350)); // {5000 : 1, 2000 : 1, 1000 : 1, 200 : 1, 100 : 1, 50 : 1 }
console.log(atm(2570));   // Incorrect value
console.log(atm(100050)); // Limit exceeded

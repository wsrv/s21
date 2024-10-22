// const fs = require('fs');
// const path = require('path');

// const folderPath = path.join(__dirname, 'files/fsHard');

// // Function to calculate the total size of files in a folder
// const calculateTotalSize = async (folderPath) => {
//   const files = await fs.promises.readdir(folderPath);
//   let totalSize = 0;

//   for (const file of files) {
//     const filePath = path.join(folderPath, file);
//     const stats = await fs.promises.stat(filePath);
//     totalSize += stats.size;
//   }

//   return totalSize;
// };

// const displayProgressBar = (currentSize, totalSize) => {
//   const percentage = (currentSize / totalSize) * 100;
//   const progressBar = '='.repeat(Math.floor(percentage / 2)) + '>';
//   process.stdout.clearLine();
//   process.stdout.cursorTo(0);
//   process.stdout.write(`Progress: [${progressBar.padEnd(50)}] ${percentage.toFixed(2)}%`);
// };

// const simulateFileDownload = async () => {
//   const files = await fs.promises.readdir(folderPath);
//   const totalSize = await calculateTotalSize(folderPath);
//   let currentSize = 0;

//   console.log(`Total size to download: ${totalSize} bytes\n`);

//   for (const file of files) {
//     const filePath = path.join(folderPath, file);
//     const stats = await fs.promises.stat(filePath);
//     const fileSize = stats.size;

//     // "Loading" a file (emulation) with a delay of 1 second
//     await new Promise((resolve) => {
//       setTimeout(() => {
//         currentSize += fileSize;
//         displayProgressBar(currentSize, totalSize);

//         if (currentSize === totalSize) {
//           console.log('\nDownload complete!\n');
//         }

//         resolve();
//       }, 1000);
//     });
//   }
// };

// const progressbar = async () => {
//   await simulateFileDownload();
// }

// progressbar();





// const fs = require('fs');
// const path = require('path');

// const folderPath = './files'; // Путь к папке с файлами
// let totalSize = 0; // Общий размер всех файлов
// let loadedSize = 0; // Размер загруженных файлов

// // Функция для подсчета общего размера всех файлов в папке
// function calculateTotalSize() {
//     const files = fs.readdirSync(folderPath);
//     totalSize = files.reduce((acc, file) => {
//         const filePath = path.join(folderPath, file);
//         const stats = fs.statSync(filePath);
//         return acc + stats.size;
//     }, 0);
// }

// // Функция для обновления прогрессбара
// function updateProgressBar(fileSize) {
//     loadedSize += fileSize;
//     const progress = Math.floor((loadedSize / totalSize) * 100);
//     process.stdout.clearLine();
//     process.stdout.cursorTo(0);
//     process.stdout.write(Progress: ${progress}%);
// }

// // Считываем размеры файлов и обновляем прогрессбар
// calculateTotalSize();
// const files = fs.readdirSync(folderPath);
// files.forEach(file => {
//     const filePath = path.join(folderPath, file);
//     const stats = fs.statSync(filePath);
//     updateProgressBar(stats.size);
// });

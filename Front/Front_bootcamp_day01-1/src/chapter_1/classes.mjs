/*
У экземпляра класса должны присутствовать св-ва:
-name string.
-grade string Для простоты предположим, что система грейдов будет иметь значения
от L1 до L4. -hardSkills string[]. -company string.


Так же должны иметься три метода:

-changeCompany(newCompanyName) - сотрудник может сменить компанию, либо же
просто уволиться. -upGrade() - сотрудник может повысить квалификацию.
-addSkill(newSkillName) - сотрудник может дополнить список своих скиллов.
*/

export class Employee {
  constructor(name, grade, hardSkills, company) {
    this.name = name;
    this.grade = grade;
    this.hardSkills = hardSkills;
    this.company = company;
  }

  changeCompany(newCompanyName) { this.company = newCompanyName; }

  upGrade() {
    if (this.grade === 'L1') {
      this.grade = 'L2';
    } else if (this.grade === 'L2') {
      this.grade = 'L3';
    } else if (this.grade === 'L3') {
      this.grade = 'L4';
    }
  }

  addSkill(newSkillName) { this.hardSkills.push(newSkillName); }
}

export default Employee;

// const boba = new Employee('Nurlan', 'L2', [ 'sleeping' ], 'BOBA Inc.');
// console.log(boba);
// boba.changeCompany('BIBA Corp.');
// boba.upGrade();
// boba.addSkill('eating');
// console.log(boba);

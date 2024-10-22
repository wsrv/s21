/* В продолжение прошлого задания вам нужно нужно создать 5 новых классов:

**Company** - класс описывающий IT компанию. Состоит из:
1. Св-ва:
- companyName
- currentProjects - текущий пулл проектов. Массив экземпляров класса Project
- completedProjects - пулл завершенных проектов. Массив экземпляров класса
Project
- staff - весь пулл сотрудников компании. Это объект, у которого есть поля
Developers, Managers. В этих полях лежат массивы экземпляров аналогичных
классов.
2. Методы:
- addNewCompanyMember() - позволяет нанять нового сотрудника. В результате
метода у выбранного сотрудника должно смениться имя компании.
- addProject() - позволяет добавить проект в пулл текущих.
- getMembersQuantity() - позволяет получить кол-во сотрудников, работающих в
данной компании
- completeProject(project) - позволяет закончить проект. В результате выполнения
функции проект из currentProjects перемещается в completedProjects. У команды
данного проекта должно увеличиться кол-во завершенных проектов.

**Project** - класс описывающий проект компании. На проекте может быть только 1
менеджер! Каждый сотрудник может работать только над одним проектом! Состоит из:
1. Св-ва:
- projectName
- minQualification - минимальная квалификация сотрудника, для работы на данном
проекте.
- team - команда проекта. Объект, типа {manager: Manager, developers: {Frontend
: [], backend: []}}. В св-ва этого объекта указан массив аналогичных классов.

2. Методы:
- addNewProjectMember(member) - Метод внутри которого вызывается проверка
менеджера на то, подходит ли сотрудник проекту. Если подходит, то команда
расширяется, иначе нет.


**Backend Developer** - Класс, который наследуется от класса Employee.
1.Имеет новые св-ва:
- stack - Массив в котором указаны технологии, которыми владеет разработчик.
- developerSide - 'backend'
- projectQuantity - Число завершенных проектов.
2. Методы:
- expandStack(someTech) - разработчик может увеличить стек технологий.

**Frontend Developer** - Класс, который наследуется от класса Employee.
1.Имеет новые св-ва:
- stack - Массив в котором указаны технологии, которыми владеет разработчик.
- developerSide - 'frontend'
- projectQuantity - Число завершенных проектов.
- projectQuantity - Число завершенных проектов.
2. Методы:
- expandStack(someTech) - разработчик может увеличить стек технологий.

**Manager** - Класс, который наследуется от класса Employee.
1.Имеет новые св-ва:
- projectQuantity - Число завершенных проектов.
2. Методы:
- checkMember(minQualification, member) - менеджер проверяет, удовлетворяет ли
сотрудник условиям проекта. Сотрудник, состоящий в другой компании не может
работать над проектом другой компании.

*/

import Employee from "./classes.mjs";

/* Св-ва и методы класса
companyName - string
currentProjects - Массив экземпляров класса Project
completedProjects -  Массив экземпляров класса Project
staff - {
    developers :  {
    frontend : массив содержащий экземпляры класса FrontendDeveloper
    backend : массив содержащий экземпляры класса BackendDeveloper
    },
    managers: массив содержащий экземпляры класса Manager
}

addNewCompanyMember(Developer/Manager) - в кач-ве аргумента принимает экземпляр
класса FrontendDeveloper, BackendDeveloper или Manager
addProject(Project) - в
кач-ве аргумента принимает экземпляр класса Project
getMembersQuantity()
completeProject()
*/
export class Company {
  constructor(companyName) {
    this.companyName = companyName;
    this.currentProjects = [];
    this.completedProjects = [];
    this.staff = {developers : {frontend : [], backend : []}, managers : []};
  }
  addNewCompanyMember(member) {
    if (member instanceof Employee) {
      member.changeCompany(this.companyName);
      if (member instanceof Manager)
        this.staff.managers.push(member);
      else if (member instanceof FrontendDeveloper)
        this.staff.developers.frontend.push(member);
      else if (member instanceof BackendDeveloper)
        this.staff.developers.backend.push(member);
    } else
      console.log('wrong object');
  }
  addProject(project) { this.currentProjects.push(project); }
  getMembersQuanity() {
    return this.staff.managers.length + this.staff.developers.frontend.length +
           this.staff.developers.backend.length;
  }
  completeProject(project) {
    if (this.currentProjects !=
        this.currentProjects.filter(p => p !== project)) {
      this.currentProjects = this.currentProjects.filter(p => p !== project);
      this.completedProjects.push(project);
      project.team.Manager.projectQuantity =
          project.team.Manager.projectQuantity + 1;
      project.team.developers.backend.forEach(element => {
        element.projectQuantity = element.projectQuantity + 1;
      });
      project.team.developers.frontend.forEach(element => {
        element.projectQuantity = element.projectQuantity + 1;
      });
      //   project.team.
    }
  }
}

/*
- projectName - string
- minQualification -string
- team -  {
   manager : экземпляр класса Manager
   developers: {
   frontend : массив содержащий экземпляры класса FrontendDeveloper
   backend : массив содержащий экземпляры класса BackendDeveloper
   }
}

addNewProjectMember(Developer) - Метод внутри которого вызывается проверка
менеджера на то, подходит ли сотрудник проекту. Если подходит, то команда
расширяется, иначе нет.
*/

export class Project {
  constructor(project, minQualification) {
    this.projectName = project;
    this.minQualification = minQualification;
    this.team = {developers : {frontend : [], backend : []}, Manager};
  }
  addNewProjectMember(member) {
    if (member instanceof Employee && member.grade >= this.minQualification) {
      if (member instanceof Manager)
        this.team.Manager = member;
      else if (member instanceof BackendDeveloper)
        this.team.developers.backend.push(member);
      else if (member instanceof FrontendDeveloper)
        this.team.developers.frontend.push(member);
    }
  }
}
/*
projectQuantity - number
checkMember(minQualification, member) - в качестве аргумента принимается строка
('L1'/'L2'/'L3'/'L4') и BackendDeveloper || FrontendDeveloper
*/
export class Manager extends Employee {
  constructor(name, grade, hardSkills, company) {
    super(name, grade, hardSkills, company);
    this.projectQuantity = 0;
  }
  checkMember(minQualification, member) {
    if (member.company !== this.companyName)
      return false;
    if (member.grade >= minQualification)
      return true;
    return false;
  }
}

/*
stack - массив строк
- developerSide - строка ('frontend')
- projectQuantity - number
expandStack(newTech) - в кач-ве аргумента принимает строку
*/

export class FrontendDeveloper extends Employee {
  constructor(name, grade, hardSkills, company, stack) {
    super(name, grade, hardSkills, company);
    this.stack = stack;
    this.developerSide = 'frontend';
    this.projectQuantity = 0;
  }
  expandStack(someTech) { this.stack.push(someTech); }
}

/*
stack - массив строк
- developerSide - строка ('backend')
- projectQuantity - number
expandStack(newTech) - в кач-ве аргумента принимает строку
*/

export class BackendDeveloper extends Employee {
  constructor(name, grade, hardSkills, company, stack) {
    super(name, grade, hardSkills, company);
    this.stack = stack;
    this.developerSide = 'backend';
    this.projectQuantity = 0;
  }
  expandStack(someTech) { this.stack.push(someTech); }
}

/*-----------------------tests-----------------------
const man = new Manager('boba1 biba', 'L2', [ 'talk' ], 'test_company_name');
const bd1 =
    new BackendDeveloper('boba2 biba', 'L2', [ 'sleep' ], 'test_company_name');
const fd1 =
    new FrontendDeveloper('boba3 biba', 'L3', [ 'sleep' ], 'test_company_name');
const bd2 =
    new BackendDeveloper('boba4 biba', 'L2', [ 'sleep' ], 'test_company_name');
const fd2 =
    new FrontendDeveloper('boba5 biba', 'L3', [ 'sleep' ], 'test_company_name');
const loh =
    new FrontendDeveloper('boba6 biba', 'L1', [ 'sleep' ], 'test_company_name');
const test_company = new Company('test_company_name')
const test_project = new Project('test_project_name', 'L2')
console.log(test_company);
console.log(test_project.team.Manager);
console.log(test_project.team.developers.backend);
console.log(test_project.team.developers.frontend);
test_company.addNewCompanyMember(man);
test_company.addNewCompanyMember(bd1);
test_company.addNewCompanyMember(bd2);
test_company.addNewCompanyMember(fd1);
test_company.addNewCompanyMember(fd2);
test_company.addNewCompanyMember(loh);
test_company.addProject(test_project);
test_project.addNewProjectMember(man);
test_project.addNewProjectMember(bd1);
test_project.addNewProjectMember(bd2);
test_project.addNewProjectMember(fd1);
test_project.addNewProjectMember(fd2);
test_project.addNewProjectMember(loh);
test_company.completeProject(test_project);
console.log(test_company.staff.developers.frontend);
console.log(test_project.team.developers.backend);
console.log(test_project.team.developers.frontend);
console.log(test_company.getMembersQuanity());*/

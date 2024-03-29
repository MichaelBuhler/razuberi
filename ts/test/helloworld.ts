interface Person {
  firstName: string
  lastName: string
  new(firstName: string, lastName: string)
  toString(): string
}

(function () {
  configure()
  // @ts-expect-error
  john || console.log("john is not defined")
  var john = instantiate()
  john && console.log("john is now defined")
  print()
  check(john)
  try {
    defenestrate()
  } catch (e) {
    console.log('Caught this:', e)
  }

  function print () {
    console.log(john)
  }
})()

function instantiate () : Person {
  var p =  new Person('John', 'Doe')
  return p
}

function configure () {
  Person.prototype.toString = function (this: Person) : string {
    return 'Person: ' + this.firstName + ' ' + this.lastName
  }
}

function check (person: Person) {
  console.log('person.firstName == \\"Doe\\" =>', person.firstName == "Doe")
  // @ts-expect-error
  console.log('person.fake === undefined =>', undefined === person.fake)
  console.log('undefined !== null =>', undefined !== null)
  console.log('13413.345134 % 6786.786 =>', 13413.345134 % 6786.786)
  console.log('typeof person:', typeof person)
  console.log('typeof Person:', typeof Person)
  console.log('void 0:', void 0)
  console.log('!false:', !false)
  console.log('1 / -0 === -Infinity:', 1 / -0 === -Infinity)
  const temp = { 0: true, a: 123, 'str': 'c', person}
  console.log(temp.a)
  console.log(temp.str)
  console.log(temp.person)
  console.log('"log" in console:', "log" in console)
}

function defenestrate () {
  throw new Person("Jane", "Doe")
}

function Person (this: Person, firstName: string, lastName: string) {
  this.firstName = firstName;
  this.lastName = lastName;
}

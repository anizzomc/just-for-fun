## Project Description
This is an object-oriented programing framework for C, which supports
    - Polymorphism
    - Encapsulation
    - Inheritance
    - Abstraction

## Strategies
### Objects and Members : Encapsulation and Abstraction
Objects are represented by a pointer to a `struct` that has at least a reference to it's defining class `class`
```
struct String_c {
  struct Class_c* clazz;
  char *str;
};
```
So, it is always possible to know an object's class by casting a pointer to `Object` and accessing the `class` member 
The other members store the other properties of the object.

### Classes
Classes allow the creation of new objects and invocation of methods.

```
struct StringClass_c {
  Class_t clazz;
  Class_t superclazz;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};
```
The code `obj->clazz[method](obj, arg)` allows to execute the `method` associated with the `obj` over such object.
Classes also have their own class, so it can execute methods such as `new`

### Methods : Polymorphism and Inheritance
Classes have their own methods, there is no dynamic method dispatching. When classes are initialized, the `methods` array is
initialized from the top of the inheritance chain to the concrete object overriding the previous initialization.

The class source code has to define 3 functions in the following format: Where <Class> is replaced for the corresponding class, for example: For `String` it will be `loadString`, `loadStringClass` and `ClassLoader_String`
#### The class initializer: `load<Class>(Class_t clazz);`
It initializers the current class. It needs to call first the initializer of the super class and then,
override it's own methods.
#### The class object initializer: `load<Class>Class(Class_t clazz);`
It initializers the current class object. It needs to call first the initializer of the super class and then,
override it's own methods.

#### The discoverable initializer: `ClassLoader_<Class>();`
The calls the class initializer and the class object initializer to be discovered by the class initializer generator `classLoader.sh` 


To invoke a method, the function `send` it is used that will access the `class` member, and then the `methods` member. All methods are defined by
and enum, so, polymorphism is achieved. If a method is not overriden, then it is inherited, and inheritance is achieved.

### Limitations
- Each class needs to re-define the members of the super-class. This is because `struct` can't be extended natively.

#### Project Structure
- The folder `classes` contains the source code (.c) for each class. 
- The folder `include` has the headers that needs to be included to use a class in a program source code
- The folder `include/extend` has the headers required to be included in the classes when extending a class.
- The file `include/Methods.h` define all available methods. This enum is shared globally and has the intention to support the function array and overriding mechanism

For example:

The class `String` which extends `Object` has following associated files:
    - include/String.h : it defines what is a `String` class is and what a pointer to a object of type `String_t` is
    - include/extend/String.h: it defines what functions are necessary to made visible for the class initializer and, any extending class.
    - classes/String.c : has the implementation of the `String` class. It includes the headers of itself and Object class.

## How to create a new Class
- To create a new Class, you need to create the required files associated to the Class: the source-code, the class header and the extension header
- Unless stated, you need to assume it extends `Object`.
- The class header should state which is the super class, and list all the methods that this class will implement.
- The source-code file should define the required structs and all extension functions

## How to add a new Method
- You need to add the name of the method into enum `Invoke_t` in the `include/Methods.h` file. Make sure it is not the last entry.
- The implementation of such method has to be treated as a private function in the source-code file, prefixed with `static` and with `_`



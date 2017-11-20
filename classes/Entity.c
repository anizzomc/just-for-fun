
#include <extend/Entity.h>
#include <String.h>

struct Entity_c {
  struct Class_c* class;
  int id;
};

struct EntityClass_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t *methods;
  int idCounter;
};

typedef struct EntityClass_c* EntityClass_t;

static struct EntityClass_c entity = {};
static struct Class_c entityClass = {};

const Class_t Entity = &entity;
const Class_t EntityClass = &entityClass;

static void _init(Entity_t this, va_list* list) {
  this->id = send(Entity, nextID);
}

static String_t _toString(Entity_t this, va_list* list) {
  char ret[64];
  sprintf(ret, "Entity(%d)", this->id);
  return send(String, new, ret);
}

static int _equals(Entity_t this, va_list* list) {
  Entity_t other = va_arg(*list, Entity_t);
  if(other == NULL) {
    return false;
  }

  if(this->class != other->class) {
    return false;
  }

  return this->id == other->id;
}

static int _getId(Entity_t this, va_list* list) {
  return this->id;
}

static int _nextID(EntityClass_t this, va_list* list) {
  return this->idCounter++;
}


void loadEntity(Class_t class) {
  loadObject(class);

  struct EntityClass_c *clazz = class;

  // Basic Properties
  clazz->class = EntityClass;
  clazz->superclass = Object;
  clazz->name = "Entity";
  clazz->instanceSize = sizeof(struct Entity_c);

  // Custom Properties
  clazz->idCounter = 1;

  // Instance Methods
  clazz->methods[init] = (Method_t) &_init;
  clazz->methods[toString] = (Method_t) &_toString;
  clazz->methods[equals] = (Method_t) &_equals;
  clazz->methods[getId] = (Method_t) &_getId;
}


void loadEntityClass(Class_t class) {
  loadClass(class);

  class->name = "EntityClass";
  // Class Methods of Entity
  class->methods[nextID] = (Method_t)&_nextID;
}

void ClassLoader_Entity() {
  loadEntity(Entity);
  loadEntityClass(EntityClass);
}



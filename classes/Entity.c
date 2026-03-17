
#include <extend/Entity.h>
#include <String.h>

struct Entity_c {
  struct Class_c* clazz;
  int id;
};

struct EntityClass_c {
  Class_t clazz;
  Class_t superclazz;
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

static const Class_t clazz = &entity;

static void _init(Entity_t thiz, va_list* list) {
  thiz->id = send(Entity, nextID);
}

static String_t _toString(Entity_t thiz, va_list* list) {
  char ret[64];
  sprintf(ret, "Entity(%d)", thiz->id);
  return send(String, new, ret);
}

static int _equals(Entity_t thiz, va_list* list) {
  Entity_t other = va_arg(*list, Entity_t);
  if(other == NULL) {
    return false;
  }

  if(thiz->clazz != other->clazz) {
    return false;
  }

  return thiz->id == other->id;
}

static int _getId(Entity_t thiz, va_list* list) {
  return thiz->id;
}

static int _nextID(EntityClass_t thiz, va_list* list) {
  return thiz->idCounter++;
}


void loadEntity(Class_t clazz) {
  loadObject(clazz);

  struct EntityClass_c *ec = clazz;

  // Basic Properties
  ec->clazz = EntityClass;
  ec->superclazz = Object;
  ec->name = "Entity";
  ec->instanceSize = sizeof(struct Entity_c);

  // Custom Properties
  ec->idCounter = 1;

  // Instance Methods
  ec->methods[init] = (Method_t) &_init;
  ec->methods[toString] = (Method_t) &_toString;
  ec->methods[equals] = (Method_t) &_equals;
  ec->methods[getId] = (Method_t) &_getId;
}


void loadEntityClass(Class_t clazz) {
  loadClass(clazz);

  clazz->name = "EntityClass";
  // Class Methods of Entity
  clazz->methods[nextID] = (Method_t)&_nextID;
}

void ClassLoader_Entity() {
  loadEntity(Entity);
  loadEntityClass(EntityClass);
}


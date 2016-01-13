#ifndef __MODULE_H
#define __MODULE_H

struct Collider;

class Module {

public:
	Module(){};
	virtual ~Module(){};
	virtual bool Init(){ return true; };
	virtual bool Start(){ return true; };
	virtual bool PreUpdate(){ return true; };
	virtual bool Update(){ return true;  };
	virtual bool PostUpdate(){ return true;  };
	virtual bool CleanUp(){ return true; };

	virtual void OnCollision(Collider* a, Collider* b)
	{}

	bool enable = true;
};
#endif //__MODULE_H
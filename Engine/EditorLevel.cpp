#include"EditorLevel.h"

void EditorLevel::Add( PhysicsMat&  lo)
{
	Object obj(lo);
	auto it = std::find(obj.samples.begin(), obj.samples.end(), lo);
	int i = obj.samples.begin() - it;
	obj.type = EditorLevel::Object::Type(i);
	objects.emplace_back(obj);
}

void EditorLevel::Remove(const EditorLevel::Object & lo)
{
	auto it = std::find(objects.begin(), objects.end(), lo);
	if (it!=objects.end())
	{
		objects.erase(it);
	}
}


EditorLevel::Object::Type EditorLevel::GetType(const Object& lo)
{
	
	auto it = std::find(objects.begin(), objects.end(), lo);
	
	if (it != objects.end())
	{
		return it->type;
	}
	return Object::Type::NoType;
}
void EditorLevel::Draw(Graphics& gfx)
{
	for (Object& obj : objects)
	{
		obj.mat->Draw(gfx);
	}
}

void EditorLevel::Save(std::string filename)
{
	std::ofstream fout(filename, std::ios::binary);
	PhysicsMat* m;
	
	for (auto i = objects.begin(); i != objects.end(); i++)
	{
		//dont wanna just put a random address in the .lvl file with the PhysicsMat pointer 
		//so make the pointer point to a nullptr and then return its address so i can still see the level
		int size = sizeof(Object) - sizeof(i->samples);
		m = i->mat;
		i->mat = nullptr;
		fout.write(reinterpret_cast<char*>(i._Ptr),sizeof(*i) - sizeof(i->samples));
		size = int(fout.tellp()) - sizeof(i->samples);
		//fout.seekp(int(fout.tellp()) - sizeof(i->samples));
		size = fout.tellp();
		i->mat = m;
	}
	int size = fout.tellp();
	fout.close();
}

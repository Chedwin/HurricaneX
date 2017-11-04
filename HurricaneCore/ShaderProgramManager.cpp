#include "ShaderProgramManager.h"
#include "Debugger.h"

using namespace HurricaneEngine;

UNIQUE_PTR(ShaderProgramManager) ShaderProgramManager::_shaderProgManager(nullptr); // Declare static unique pointer

																					// Static pointer retrieval
ShaderProgramManager* ShaderProgramManager::GetShaderManager() {
	if (_shaderProgManager.get() == nullptr) {
		_shaderProgManager.reset(new ShaderProgramManager());
	}
	return _shaderProgManager.get();
}


// Empty the resource map upon destruction
ShaderProgramManager::~ShaderProgramManager()
{
	_shaderResources.EmptyResourceMap();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INSERT shader by name
ResourceHandle<ShaderProgram> ShaderProgramManager::StoreShaderProg(const STRING& _name, ShaderProgram* _sp)
{
	ResourceHandle<ShaderProgram> result(-1);
	result = _shaderResources.GetHandle(_name);

	if (!result.IsNull()) {
		// throw exception
	}

	result = _shaderResources.Add(_name, _sp);
	return result;
}

// GET shader handle in the resource map by name
ResourceHandle<ShaderProgram> ShaderProgramManager::GetShaderProgHandle(const STRING& _name)
{
	return _shaderResources.GetHandle(_name);
}

// GET shader program by handle
ShaderProgram* ShaderProgramManager::GetShaderProgram(ResourceHandle<ShaderProgram>& _handle)
{
	return _shaderResources.GetResource(_handle);
}

// GET shader program by name
ShaderProgram* ShaderProgramManager::GetShaderProgram(const STRING & _name)
{
	ShaderProgram* result = nullptr;
	ResourceHandle<ShaderProgram> handle = _shaderResources.GetHandle(_name);

	if (handle.IsNull()) {
		Debugger::Error("Shader named '" + _name + "' does not exist in ShaderManager");
		return result;
	}
	result = ShaderProgramManager::GetShaderProgram(handle);
	return result;
}

// DELETE shader program by name
void ShaderProgramManager::DeleteShaderProgram(STRING& _name)
{
	_shaderResources.Remove(_name);
}
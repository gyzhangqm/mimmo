#include <fstream>
#include "Operators.hpp"

/*!Overloaded function of base class setInput.
 * It sets the input/result and write on file at the same time.
 * \param[in] data Pointer to data to be written and to be used to set the input/result.
 */
template<typename T>
void
mimmo::GenericOutput::setInput(T* data){
	BaseManipulation::setInput(data);
	BaseManipulation::setResult(data);
	std::ofstream file;
	file.open(m_filename);
	if (file.is_open()){
		file << *data;
		file.close();
	}
}

/*!Overloaded function of base class setInput.
 * It sets the input/result and write on file at the same time.
 * \param[in] data Data to be written and to be used to set the input/result.
 */
template<typename T>
void
mimmo::GenericOutput::setInput(T& data){
	BaseManipulation::setInput(data);
	BaseManipulation::setResult(data);
	std::ofstream file;
	file.open(m_filename);
	if (file.is_open()){
		file << data;
		file.close();
	}
}

// OLD BASEMANIPULATION CLASS TEMPLATED INPUT/RESULT METHODS //

/*!It gets the input member of the object.
 * \return Pointer to data stored in the input member.
 */
template<typename T>
T*
mimmo::GenericOutput::getInput(){
	return(static_cast<IODataT<T>*>(m_input.get())->getData());
}

/*!It sets the result member of the object.
 * \param[in] data Pointer to data to be stored in the result member.
 */
template<typename T>
void
mimmo::GenericOutput::setResult(T* data){
	clearResult();
	std::unique_ptr<IOData> dummy(new IODataT<T>(*data));
	m_result = std::move(dummy);
}

/*!It sets the result member of the object.
 * \param[in] data Data to be stored in the result member.
 */
template<typename T>
void
mimmo::GenericOutput::setResult(T& data){
	clearResult();
	std::unique_ptr<IOData> dummy(new IODataT<T>(data));
	m_result = std::move(dummy);
}

/*!It gets the result member of the object.
 * \return Pointer to data stored in the result member.
 */
template<typename T>
T*
mimmo::GenericOutput::getResult(){
	return(static_cast<IODataT<T>*>(m_result.get())->getData());
}



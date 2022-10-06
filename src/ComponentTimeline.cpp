

#include <ComponentTimeline.h>



extern "C" {


ComponentTimeline::ComponentTimeline(const char* xmlFName) {

	
	std::cout << "ComponentTimeline::ComponentTimeline() -- CONSTRUCTOR CALLED" << std::endl;

	// INITIALIZE MANAGER-XML
	ManagerXML* managerXML = new ManagerXML("resources/data_anim.xml");		


	m_xmlData = managerXML->GetXmlOutput();



}



ComponentTimeline::~ComponentTimeline() {

	std::cout << "ComponentTimeline::ComponentTimeline() -- DESTRUCTOR CALLED" << std::endl;



}




void ComponentTimeline::Initialize() {

	std::cout << "ComponentTimeline::Initialize() -- FUNCTION CALLED" << std::endl;

	// GETTING TRANSFORM COMPONENT
	m_playerComponent = owner->GetComponent<ComponentPlayer>();


}



void ComponentTimeline::Update() {
	std::cout << "ComponentTimeline::Update() -- FUNCTION CALLED" << std::endl;


}




void ComponentTimeline::Render() {
	std::cout << "ComponentTimeline::Render() -- FUNCTION CALLED" << std::endl;






}




}



#include "GUI.h"
#include<iostream>

using namespace std;


CEGUI::OpenGL3Renderer* GUI::m_renderer = nullptr;;

void GUI::init(const std::string& resourceDir)
{

	if (m_renderer == nullptr)
	{
		
		m_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();

		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
		rp->setResourceGroupDirectory("imagesets", resourceDir + "/imagesets/");
		rp->setResourceGroupDirectory("schemes", resourceDir + "/schemes/");
		rp->setResourceGroupDirectory("fonts", resourceDir + "/fonts/");
		rp->setResourceGroupDirectory("layouts", resourceDir + "/layouts/");
		rp->setResourceGroupDirectory("looknfeels", resourceDir + "/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", resourceDir + "/lua_scripts/");

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

	}

	m_context = &CEGUI::System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	m_context->setRootWindow(m_root);
}


void GUI::draw()
{
	
	m_renderer->beginRendering();

	m_context->draw();

	m_renderer->endRendering();
	cout << "\n Drawn Successfully!";
	glDisable(GL_SCISSOR_TEST);
	
	
}

void GUI::loadScheme(const std::string& schemeFile)
{
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

CEGUI::Window* GUI::createWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name)
{
	CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	m_root->addChild(newWindow);
	setWidgetDestRect(newWindow, destRectPerc, destRectPix);
	return newWindow;
}

void GUI::setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix)
{
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
	widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
}

void GUI::setFont(const std::string& fontFile)
{
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	m_context->setDefaultFont(fontFile);

}

void GUI::destroy()
{
	CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}
#pragma once
#include "Limux.h"
namespace LMX
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender(Timestep ts) override;
		void OnEvent(Event& e, Timestep ts) override;
	private:
		Ref<Scene> m_Scene;
		Ref<Shader> m_Shader;
		Ref<Framebuffer> m_Framebuffer;
		Entity m_Model;
		Entity m_Camera;
		
		
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	};
}


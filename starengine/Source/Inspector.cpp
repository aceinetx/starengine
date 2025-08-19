#include "Director.h"
#include "Node.h"
#include "fmt/base.h"
#include "imgui.h"
#include <fmt/format.h>
#include <string>
#include <typeinfo>

using namespace star;

static std::string getNodeName(Node* node) {
	const char* name = typeid(*node).name();
	return name;
}

static unsigned int nodeIndex = 0;
static Node* selectedNode = nullptr;

// Iterate children (Draw tree)
static void iterateChildren(Node* node) {
	std::string title = fmt::format("{}##{}", getNodeName(node), nodeIndex);
	if (ImGui::TreeNode(title.c_str())) {
		for (Node* child : node->getChildren()) {
			iterateChildren(child);
		}
		ImGui::TreePop();
	}
	if (ImGui::IsItemClicked()) {
		selectedNode = node;
	}
	nodeIndex++;
}

void Director::drawInspector() {
	ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	nodeIndex = 0;
	iterateChildren(getRunningScene());
	ImGui::End();

	// Properties window
	if (selectedNode) {
		ImGui::SetNextWindowPos({200, 200}, ImGuiCond_Once);
		ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
		// Position
		float pos[2] = {selectedNode->getPositionX(), selectedNode->getPositionY()};
		ImGui::DragFloat2("Position", pos);
		selectedNode->setPositionX(pos[0]);
		selectedNode->setPositionY(pos[1]);

		// Scale
		float scale = selectedNode->getScale();
		ImGui::DragFloat("Scale", &scale, 0.01f);
		selectedNode->setScale(scale);

		// Zoom (if camera)
		if (auto camera = dynamic_cast<Camera*>(selectedNode)) {
			float zoom = camera->getZoom();
			ImGui::DragFloat("Zoom", &zoom, 0.01f);
			camera->setZoom(zoom);
		}

		// Close button
		if (ImGui::Button("Close")) {
			selectedNode = nullptr;
		}
		ImGui::End();
	}
}

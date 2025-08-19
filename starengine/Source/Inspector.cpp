#include "Director.h"
#include "Node.h"
#include "fmt/base.h"
#include "imgui.h"
#include <cstdio>
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
	bool open = ImGui::TreeNode(title.c_str());
	if (ImGui::IsItemClicked()) {
		selectedNode = node;
	}
	if (open) {
		for (Node* child : node->getChildren()) {
			iterateChildren(child);
		}
		ImGui::TreePop();
	}
	nodeIndex++;
}

void Director::drawInspector() {
	// Inspector window
	ImGui::Begin("StarEngine Inspector", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	nodeIndex = 0;
	iterateChildren(getRunningScene());
	auto inspectorPos = ImGui::GetWindowPos();
	auto inspectorSize = ImGui::GetWindowSize();
	ImGui::End();

	// Properties window
	ImGui::SetNextWindowPos({inspectorPos.x + inspectorSize.x, inspectorPos.y});
	ImGui::Begin("> Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	if (selectedNode) {
		// Position
		float pos[2] = {selectedNode->getPositionX(), selectedNode->getPositionY()};
		ImGui::DragFloat2("Position", pos);
		selectedNode->setPositionX(pos[0]);
		selectedNode->setPositionY(pos[1]);

		// Scale
		float scale = selectedNode->getScale();
		ImGui::DragFloat("Scale", &scale, 0.01f);
		selectedNode->setScale(scale);

		// Rotation
		float rotation = selectedNode->getRotation();
		ImGui::DragFloat("Rotation", &rotation, 0.1f);
		selectedNode->setRotation(rotation);

		// Zoom (if camera)
		if (auto camera = dynamic_cast<Camera*>(selectedNode)) {
			float zoom = camera->getZoom();
			ImGui::DragFloat("Zoom", &zoom, 0.01f);
			camera->setZoom(zoom);
		}
	}

	ImGui::End();
}

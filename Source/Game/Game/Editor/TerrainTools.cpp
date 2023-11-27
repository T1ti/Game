#include "TerrainTools.h"

#include "Game/Util/ImguiUtil.h"

namespace Editor
{
	TerrainTools::TerrainTools()
		: BaseEditor(GetName(), true)
	{

	}

	void TerrainTools::DrawImGui()
	{
		if (ImGui::Begin(GetName()))
		{

			Util::Imgui::GroupHeader("Editing Mode");
			if (ImGui::BeginTable("Editing Mode Table", 2))
			{
				Util::Imgui::ColumnRadioButton("Terrain", &_EditingMode, static_cast<i32>(EditingMode::TERRAIN));
				Util::Imgui::ColumnRadioButton("Texturing", &_EditingMode, static_cast<i32>(EditingMode::TEXTURING));

				ImGui::EndTable();
			}

			if (_EditingMode == static_cast<i32>(EditingMode::TERRAIN))
			{
				Util::Imgui::GroupHeader("Terrain Modes");
				if (ImGui::BeginTable("Brush Type Table", 2))
				{
					Util::Imgui::ColumnRadioButton("Raise/Lower", &_terrainBrushTool, static_cast<i32>(TerrainBrushMode::SCULPT));
					Util::Imgui::ColumnRadioButton("Flatten", &_terrainBrushTool, static_cast<i32>(TerrainBrushMode::FLAT));
					Util::Imgui::ColumnRadioButton("Smooth (TODO)", &_terrainBrushTool, static_cast<i32>(TerrainBrushMode::SMOOTH));
					Util::Imgui::ColumnRadioButton("Vertex (TODO)", &_terrainBrushTool, static_cast<i32>(TerrainBrushMode::VERTEX));
					Util::Imgui::ColumnRadioButton("Holes (TODO)", &_terrainBrushTool, static_cast<i32>(TerrainBrushMode::HOLES));
					Util::Imgui::ColumnRadioButton("Impass (TODO)", &_terrainBrushTool, static_cast<i32>(TerrainBrushMode::IMPASS));

					ImGui::EndTable();
				}

				if (_terrainBrushTool == static_cast<i32>(TerrainBrushMode::SCULPT) || _terrainBrushTool == static_cast<i32>(TerrainBrushMode::FLAT))
				{
					Util::Imgui::GroupHeader("Falloff Types");
					if (ImGui::BeginTable("Hardness Type Table", 2))
					{
						Util::Imgui::ColumnRadioButton("Linear", &_hardnessMode, static_cast<i32>(HardnessMode::LINEAR));
						Util::Imgui::ColumnRadioButton("Smoothstep", &_hardnessMode, static_cast<i32>(HardnessMode::SMOOTHSTEP));
						Util::Imgui::ColumnRadioButton("Quadratic", &_hardnessMode, static_cast<i32>(HardnessMode::QUADRATIC));
						Util::Imgui::ColumnRadioButton("Gaussian", &_hardnessMode, static_cast<i32>(HardnessMode::GAUSSIAN));
						Util::Imgui::ColumnRadioButton("Exponential", &_hardnessMode, static_cast<i32>(HardnessMode::EXPONENTIAL));
						
						ImGui::EndTable();
					}
				}
				if (_terrainBrushTool == static_cast<i32>(TerrainBrushMode::FLAT))
				{
					if (ImGui::Checkbox("Instant pressure", &_instantPressure))
					{

					}

					// TODO : allow inputing custom locked height value?
					if (ImGui::Checkbox("Lock Height", &_lockHeight))
					{

					}
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
						ImGui::SetTooltip("Height will be locked to the initial cursor click position.");

					// todo : both/lower/raise
					const char* flattenModesNames[3] = { "Both", "Raise", "Lower" };
					const char* preview = flattenModesNames[_flattenMode];
					if (ImGui::BeginCombo("flatten mode", preview))
					{
						// std::string selectableName;
						// selectableName.reserve(128);

						for (i32 i = 0; i < static_cast<i32>(FlattenMode::count); i++ )
						{
							bool isSelected = i == _flattenMode;

							auto selectableName = flattenModesNames[i];
							if (ImGui::Selectable(selectableName, &isSelected))
							{
								_flattenMode = i;
							}

							if (isSelected)
								ImGui::SetItemDefaultFocus();
						}

						ImGui::EndCombo();
					}
				}

				ImGui::NewLine();

				Util::Imgui::GroupHeader("Brush Settings");
				Util::Imgui::FloatSlider("Hardness:", &_brushHardness, 0.0f, 1.0f, 0.01f, 0.1f, true);
				Util::Imgui::FloatSlider("Radius:", &_brushRadius, 0.0f, 500.0f, 1.0f, 10.0f, true);
				Util::Imgui::FloatSlider("Pressure:", &_brushPressure, 0.0f, 100.0f, 1.0f, 10.0f, true);

			}
			else if (_EditingMode == static_cast<i32>(EditingMode::TEXTURING))
			{
				// TODO
			}

			ImGui::NewLine();

			Util::Imgui::GroupHeader("Wireframe Color");
			Util::Imgui::ColorPicker("Wireframe Color:", &_wireframeColor, vec2(50.0f, 50.0f));
			Util::Imgui::GroupHeader("Vertex Color");
			Util::Imgui::ColorPicker("Vertex Color:", &_vertexColor, vec2(50.0f, 50.0f));
			Util::Imgui::GroupHeader("Brush Color");
			Util::Imgui::ColorPicker("Brush Color:", &_brushColor, vec2(50.0f, 50.0f));
		}

		ImGui::End();
	}
}
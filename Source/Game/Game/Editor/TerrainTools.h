#pragma once
#include "BaseEditor.h"

#include <imgui/imgui.h>

#include <Base/Math/Color.h>


namespace Editor
{
	class TerrainTools : public BaseEditor
	{
	public:
		enum class EditingMode
		{
			TERRAIN = 0,
			TEXTURING,
			WATER // might need separating tool
		};

		enum class TerrainBrushMode
		{
			SCULPT = 0,
			FLAT,
			// SMOOTH, // have it as a hardness mode?
			VERTEX_COLOR,
			HOLES,
			IMPASS,
			AREA,
			count
		};

		enum class TexturingBrushMode
		{
			Paint = 0,
			SMOOTH,// average the layer weights based on hardness
			FILL, // instantly apply the opacity(weight)
			NOISE // apply noise effects
		};

		enum class HardnessMode
		{
			LINEAR = 0,
			QUADRATIC,
			GAUSSIAN,
			EXPONENTIAL,
			SMOOTHSTEP
		};

		enum class FlattenMode
		{
			Both = 0,
			Raise,
			Lower,
			count
		};

	public:
		TerrainTools();

		virtual const char* GetName() override { return "Terrain Tools"; }

		virtual void DrawImGui() override;

		Color GetWireframeColor() { return _wireframeColor; }
		Color GetVertexColor() { return _vertexColor; }
		Color GetBrushColor() { return _brushColor; }

		f32 GetHardness() { return _brushHardness; }
		f32 GetRadius() { return _brushRadius; }
		f32 GetPressure() { return _brushPressure; }
		bool InstantPressure() { return _instantPressure; }
		bool LockedHeight() { return _lockHeight; }
		bool AllowTerrainRaise() { return _flattenMode == static_cast<i32>(FlattenMode::Both) || _flattenMode == static_cast<i32>(FlattenMode::Raise); }
		bool AllowTerrainLower() { return _flattenMode == static_cast<i32>(FlattenMode::Both) || _flattenMode == static_cast<i32>(FlattenMode::Lower); }


		i32 GetEditingMode() { return _EditingMode; }
		bool TerrainModeEnabled() { return _EditingMode == static_cast<i32>(EditingMode::TERRAIN); }
		bool TexturingModeEnabled() { return _EditingMode == static_cast<i32>(EditingMode::TEXTURING); }
		i32 GetHardnessMode() { return _hardnessMode; }
		i32 GetBrushMode() { return _terrainBrushTool; }

	private:
		i32 _EditingMode = 0;
		i32 _terrainBrushTool = 0;
		i32 _hardnessMode = 0;
		i32 _flattenMode = 0;

		f32 _brushHardness = 0.5f; // Falloff
		f32 _brushRadius = 10.0f;
		f32 _brushPressure = 10.0f; // Speed

		// For flatten mode
		bool _instantPressure = false; 
		bool _lockHeight = false;

		Color _wireframeColor = Color::Black;
		Color _vertexColor = Color::Green;
		Color _brushColor = Color::White;
	};
}
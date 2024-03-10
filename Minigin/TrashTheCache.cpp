#include "TrashTheCache.h"
#include <chrono>
#include <numeric>
#include <imgui.h>
#include <future>
#include <imgui_plot.h>

using namespace std::chrono;

Trash::Graph Trash::CalculateTrashInt(int const samples)
{
	Trash::Graph result{};

	constexpr int arrSize{ 10'000'000 };
	long long elapsedTime{};

	int* arr{ new int[arrSize] {} };

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<float> timings{};
		for (int sample = 0; sample < samples; sample++)
		{
			auto start = high_resolution_clock::now();
			for (int i = 0; i < arrSize; i += stepsize)
			{
				arr[i] *= 2;
			}
			auto end = high_resolution_clock::now();
			elapsedTime = duration_cast<microseconds>(end - start).count();
			timings.emplace_back(static_cast<float>(elapsedTime));
		}

		float averageTime{ static_cast<float>(std::accumulate(timings.begin(), timings.end(), 0.0f)) / samples };

		result.StepSizes.emplace_back(static_cast<float>(stepsize));
		result.Timings.emplace_back(averageTime);

	}

	delete[] arr;

	return result;
}

Trash::Graph Trash::CalculateTrashObject(int const samples)
{
	Trash::Graph result{};

	constexpr int arrSize{ 10'000'000 };
	long long elapsedTime{};

	GameObject* arr2{ new GameObject[arrSize] };

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<float> timings{};
		for (int sample = 0; sample < samples; sample++)
		{
			auto start = high_resolution_clock::now();
			for (int i = 0; i < arrSize; i += stepsize)
			{
				arr2[i].id = 2;
			}
			auto end = high_resolution_clock::now();
			elapsedTime = duration_cast<microseconds>(end - start).count();
			timings.emplace_back(static_cast<float>(elapsedTime));
		}

		float averageTime{ static_cast<float>(std::accumulate(timings.begin(), timings.end(), 0.0f)) / samples };

		result.StepSizes.emplace_back(static_cast<float>(stepsize));
		result.Timings.emplace_back(averageTime);
	}

	delete[] arr2;

	return result;

}

void Trash::DisplayIntWindow()
{
	ImGui::Begin("Exercise 1");
	static int samples{ 10 };
	ImGui::InputInt("# samples", &samples);

	static bool IsCalculating{ false };
	static bool DisplayGraph{ false };
	static std::future<Graph> futureIntGraph{};
	static Graph finishedIntGraph{};

	if (IsCalculating)
	{
		ImGui::Text("Calculating...");

		if (futureIntGraph.wait_for(milliseconds(0)) == std::future_status::ready)
		{
			finishedIntGraph = futureIntGraph.get();
			IsCalculating = false;
		}
	}
	else if (ImGui::Button("Trash the Cache"))
	{
		IsCalculating = true;
		DisplayGraph = true;

		//todo: make this function call async
		futureIntGraph = std::async(std::launch::async, &CalculateTrashInt, samples);
	}
	
	if (DisplayGraph and not IsCalculating)
	{
		int const valuesCount{ 11 }; 

		float xData[valuesCount]{};
		float yData[valuesCount]{};

		std::copy(finishedIntGraph.StepSizes.begin(), finishedIntGraph.StepSizes.end(), xData);
		std::copy(finishedIntGraph.Timings.begin(), finishedIntGraph.Timings.end(), yData);

		float maxTime{};

		for (auto& timing : finishedIntGraph.Timings)
		{
			if (timing > maxTime) maxTime = timing;
		}

		static ImGui::PlotConfig intPlot;
		intPlot.values.xs = xData; // this line is optional
		intPlot.values.ys = yData;
		intPlot.values.count = valuesCount;
		intPlot.scale.min = 0;
		intPlot.scale.max = maxTime;
		intPlot.tooltip.show = true;
		intPlot.tooltip.format = "x=%.0f, y=%.2f";
		intPlot.grid_x.show = true;
		intPlot.grid_y.show = true;
		intPlot.frame_size = ImVec2(200, 100);
		intPlot.line_thickness = 2.f;

		ImGui::Plot("plot", intPlot);
	}

	ImGui::End();
}

void Trash::DisplayObjectWindow()
{
	ImGui::Begin("Exercise 2");
	static int samples{ 100 };
	ImGui::InputInt("# samples", &samples);

	static bool IsCalculating{ false };
	static bool DisplayGraph{ false };
	static std::future<Graph> futureObjectGraph{};
	static Graph finishedObjectGraph{};

	if (IsCalculating)
	{
		ImGui::Text("Calculating...");

		if (futureObjectGraph.wait_for(milliseconds(0)) == std::future_status::ready)
		{
			finishedObjectGraph = futureObjectGraph.get();
			IsCalculating = false;
		}
	}
	else if (ImGui::Button("Trash the Cache"))
	{
		IsCalculating = true;
		DisplayGraph = true;

		//todo: make this function call async
		futureObjectGraph = std::async(std::launch::async, &CalculateTrashObject, samples);
	}

	if (DisplayGraph and not IsCalculating)
	{
		int const valuesCount{ 11 };

		float xData[valuesCount]{};
		float yData[valuesCount]{};

		std::copy(finishedObjectGraph.StepSizes.begin(), finishedObjectGraph.StepSizes.end(), xData);
		std::copy(finishedObjectGraph.Timings.begin(), finishedObjectGraph.Timings.end(), yData);

		float maxTime{};

		for (auto& timing : finishedObjectGraph.Timings)
		{
			if (timing > maxTime) maxTime = timing;
		}

		static ImGui::PlotConfig intPlot;
		intPlot.values.xs = xData; // this line is optional
		intPlot.values.ys = yData;
		intPlot.values.count = valuesCount;
		intPlot.scale.min = 0;
		intPlot.scale.max = maxTime;
		intPlot.tooltip.show = true;
		intPlot.tooltip.format = "x=%.0f, y=%.2f";
		intPlot.grid_x.show = true;
		intPlot.grid_y.show = true;
		intPlot.frame_size = ImVec2(200, 100);
		intPlot.line_thickness = 2.f;

		ImGui::Plot("plot", intPlot);
	}

	ImGui::End();

}

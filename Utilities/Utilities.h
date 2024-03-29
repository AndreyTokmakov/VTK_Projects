//============================================================================
// Name        : Utilities.h
// Created on  : 27.08.2021
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Utilities
//============================================================================

#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#ifndef UTILITIES_INCLUDE_GUARD
#define UTILITIES_INCLUDE_GUARD

#include <string>
#include <array>
#include <string_view>

#include <vtkBoxWidget.h>
#include <vtkColor.h>
#include <vtkNamedColors.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkMatrix3x3.h>
#include <vtkMatrix4x4.h>

// Eigen includes:
#include <Core>
#include <Dense>

namespace Utilities
{
    static constexpr size_t MAX_TEETH_COUNT { 32 };
    static constexpr size_t MAX_TEETH_NUM_PER_JAW_SIDE { MAX_TEETH_COUNT / 2 };

    // TODO: Check performance Sorted vs Unsorted
    // Teeth of the upper jaw according to the FDI notation
    static constexpr std::array<int16_t, MAX_TEETH_NUM_PER_JAW_SIDE> upperTooths {
            18,  17,  16,  15,  14,  13,  12,  11,
            21,  22,  23,  24,  25,  26,  27,  28
    };

    // TODO: Check performance Sorted vs Unsorted
    // Teeth of the lower jaw according to the FDI notation
    static constexpr std::array<int16_t, MAX_TEETH_NUM_PER_JAW_SIDE> lowerTooths {
            48,  47,  46,  45,  44,  43,  42,  41,
            31,  32,  33,  34,  35,  36,  37,  38
    };

    static constexpr uint_fast16_t MAX_LOWER_JAW_TOOTH = *std::max_element(lowerTooths.begin(), lowerTooths.end());
    static constexpr uint_fast16_t MIN_LOWER_JAW_TOOTH = *std::min_element(lowerTooths.begin(), lowerTooths.end());

    static constexpr uint_fast16_t MAX_UPPER_JAW_TOOTH = *std::max_element(upperTooths.begin(), upperTooths.end());
    static constexpr uint_fast16_t MIN_UPPER_JAW_TOOTH = *std::min_element(upperTooths.begin(), upperTooths.end());

    bool isLowerTooth([[maybe_unused]] uint_fast16_t id);
    bool isUpperTooth([[maybe_unused]] uint_fast16_t id);

    //=================================================================================//

    vtkAlgorithmOutput* readPolyData(std::string_view fileName);
    vtkSmartPointer<vtkPolyData> readStl(std::string_view fileName);
    vtkSmartPointer<vtkPolyData> readObj(std::string_view fileName);

    void WriteSTL(vtkAlgorithmOutput* data, std::string_view fileName) ;
    void WriteSTL(vtkSmartPointer<vtkPolyData> data, std::string_view fileName);


    vtkSmartPointer<vtkActor> getPolyDataActor(const vtkSmartPointer<vtkPolyData>& polyData);

    vtkSmartPointer<vtkActor> getPolyDataActor(const std::vector<vtkSmartPointer<vtkPolyData>>& data);

    vtkSmartPointer<vtkPolyData> pointsToPolyData(const std::vector<Eigen::Vector3d>& points);

    vtkSmartPointer<vtkActor> getPointsActor(const std::vector<Eigen::Vector3d>& points,
                                             const std::array<double, 3>& color = {1, 0, 0},
                                             const unsigned short size = 12);

    vtkSmartPointer<vtkActor> getLinesActor_FromPoints(const std::vector<Eigen::Vector3d>& points);

    vtkSmartPointer<vtkActor> getLineActor(const Eigen::Vector3d& pt1,
                                           const Eigen::Vector3d& pt2,
                                           const std::array<double, 3>& color = {1, 0, 0});

    [[nodiscard("Make sure to handle return value")]]
    vtkSmartPointer<vtkActor> getOutlineActor(const vtkSmartPointer<vtkPolyData>& toothData);

    [[nodiscard("Do not discard the function return value. It's not free...")]]
    vtkSmartPointer<vtkMatrix3x3> cast4x4MatrixTo3x3(const vtkSmartPointer<vtkMatrix4x4>& matrix);

    [[nodiscard("Do not discard the function return value. It's not free...")]]
    vtkSmartPointer<vtkMatrix4x4> cast3x3MatrixToVTK4x4(const Eigen::Matrix3d& matrix);

    void DisplayActors(const std::vector<vtkSmartPointer<vtkActor>>& actors,
                       const std::array<int, 2>& position = {1950, 50});

    void DisplayActorsEx(const std::vector<vtkSmartPointer<vtkProp3D>>& actors,
                         const std::array<int, 2>& position = {1950, 50});

    // Eigen::Vector3d GetCentroid(vtkSmartPointer<vtkPolyData> polyData);
    // Eigen::Vector3d GetCentroid(vtkAlgorithmOutput* polyData);


    [[nodiscard("Do not discard the function return value. It's not free...")]]
    vtkSmartPointer<vtkPolyData> rotatePolyData(const vtkSmartPointer<vtkPolyData> polyData,
                                                double x, double y, double z) noexcept;

    [[nodiscard("Do not discard the function return value. It's not free...")]]
    vtkSmartPointer<vtkPolyData> rotatePolyData(const vtkSmartPointer<vtkPolyData> polyData,
                                                const vtkSmartPointer<vtkMatrix4x4>& matrix) noexcept;

    [[nodiscard("Do not discard the function return value. It's not free...")]]
    vtkSmartPointer<vtkPolyData> moveTooth(const vtkSmartPointer<vtkPolyData>& polyData,
                                           double x, double y, double z);

    [[nodiscard("Do not discard the function return value. It's not free...")]]
    vtkSmartPointer<vtkPolyData> setPolyDataCenter(const vtkSmartPointer<vtkPolyData>& polyData,
                                                   double x, double y, double z);

    [[nodiscard("Do not discard the function return value. It's not free...")]]
    vtkSmartPointer<vtkPolyData> setPolyDataCenter(const vtkSmartPointer<vtkPolyData>& polyData,
                                                   const Eigen::Vector3d& pt);


    void visualize(vtkAlgorithmOutput* data);
    void visualize(vtkSmartPointer<vtkPolyData> data,
                   bool drawBoundingBox = false);

    void visualize(const std::vector<vtkSmartPointer<vtkPolyData>>& data,
                   bool drawBoundingBox = false);
    void visualize(const std::vector<vtkAlgorithmOutput*>& data);

    void separate_connected_components(const vtkSmartPointer<vtkPolyData>& dataPtr);
    void separate_connected_components_ex(const vtkSmartPointer<vtkPolyData>& dataPtr);
    void separate_connected_components_parallel_BAD(const vtkSmartPointer<vtkPolyData>& dataPtr);

    std::vector<vtkSmartPointer<vtkPolyData>>
    separate_connected_components_parallel_test(const vtkSmartPointer<vtkPolyData>& dataPtr);
}

#endif //!UTILITIES_INCLUDE_GUARD
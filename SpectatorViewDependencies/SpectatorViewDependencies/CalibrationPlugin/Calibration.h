#pragma once

class Calibration sealed
{
public:
    Calibration() {}

    bool Initialize();

    bool ProcessChessboardImage(
        unsigned char* image,
        int imageWidth,
        int imageHeight,
        int boardWidth,
        int boardHeight,
        unsigned char* cornersImage,
        unsigned char* heatmapImage,
        int cornerImageRadias,
        int heatmapWidth);

    bool ProcessChessboardIntrinsics(
        float squareSize,
        float* intrinsics,
        int numIntrinsics);

    bool ProcessArUcoData(
        unsigned char* image,
        int imageWidth,
        int imageHeight,
        int* markerIds,
        int numMarkers,
        float* markerCornersInWorld,
        float* markerCornersRelativeToCamera,
        float* planarCorners,
        int numMarkerCornerValues,
        float* orientation);

    bool ProcessArUcoIntrinsics(
        float* intrinsics,
        int numIntrinsics);

    bool ProcessIndividualArUcoExtrinsics(
        float* intrinsics,
        float* extrinsics,
        int numExtrinsics);

    bool ProcessGlobalArUcoExtrinsics(
        float* intrinsics,
        float* extrinsics,
        int numExtrinsics);

    bool GetLastErrorMessage(
        char* buff,
        int size);

private:
    struct corners
    {
        cv::Point3f topLeft;
        cv::Point3f topRight;
        cv::Point3f bottomRight;
        cv::Point3f bottomLeft;
    };

    void StoreIntrinsics(
        double reprojectionError,
        cv::Mat cameraMat,
        cv::Mat distCoeff,
        int width,
        int height,
        float* intrinsics);

    void StoreExtrinsics(
        float succeeded,
        cv::Mat rvec,
        cv::Mat tvec,
        float* extrinsics);

    int width = 0;
    int height = 0;
    std::vector<std::vector<cv::Point3f>> worldPointObservations;
    std::vector<std::vector<cv::Point2f>> imagePointObservations;
    std::vector<std::vector<cv::Point3f>> pointObservationsRelativeToCamera;
    std::vector<std::vector<cv::Point3f>> planarPointObservations;

    int chessboardImageWidth = 0;
    int chessboardImageHeight = 0;
    int chessboardWidth = 0;
    int chessboardHeight = 0;
    std::vector<std::vector<cv::Point2f>> chessboardImagePointObservations;
    std::string lastError;
};
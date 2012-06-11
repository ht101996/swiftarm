#include "Download.h"
#include "gtest.h"
#include <string>
#include <iostream>


class DownloadTest : public ::testing::Test {
	protected:
	
	Download *download;
	std::string tracker;
	std::string root_hash;
	std::string filename;
	int id;
	
	virtual ~DownloadTest() {}
	
	virtual void SetUp(){
		tracker = "tracker";
		root_hash = "ABCD1234ABCD1234ABCD1234ABCD1234ABCD1234";
		filename = "test";
		id = 1;
		download = new Download(tracker, root_hash, filename);
		download->setID(1);
	}
	
	virtual void TearDown() {}
	
};

/* Constructor */

TEST_F(DownloadTest, constructor) {
	
	EXPECT_EQ(tracker, download->getTrackerAddress());
	EXPECT_EQ(root_hash, download->getRootHash());
	EXPECT_EQ(filename, download->getFilename());
	EXPECT_EQ(id, download->getID());
}

/* ID */

// Trivial
TEST_F(DownloadTest, setIDTrivial) {
	
	id = 100;
	download->setID(id);
	EXPECT_EQ(id, download->getID());
}

// Negative
TEST_F(DownloadTest, setIDNegative) {
	
	int id = -5;
	download->setID(id);
	EXPECT_EQ(-1, download->getID());
}

/***********************************************
********* DOWNLOAD STATS TESTS ****************
***********************************************/

/* Download Speed */

// Trivial
TEST_F(DownloadTest, setDownloadSpeedTrivial) {
	
	double downloadSpeed = 10.5;
	download->setDownloadSpeed(downloadSpeed);
	double speed = download->getStatistics().download_speed;
	EXPECT_DOUBLE_EQ(downloadSpeed, speed);
}

// Negative
TEST_F(DownloadTest, setDownloadSpeedNegative) {
	
	double downloadSpeed = -1;
	double originalSpeed = download->getStatistics().download_speed;
	download->setDownloadSpeed(downloadSpeed);
	double speed = download->getStatistics().download_speed;
	EXPECT_DOUBLE_EQ(originalSpeed, speed);
}


/* Upload Speed */

// Trivial
TEST_F(DownloadTest, setUploadSpeedTrivial) {
	
	double uploadSpeed = 10.5;
	download->setUploadSpeed(uploadSpeed);
	double speed = download->getStatistics().upload_speed;
	EXPECT_DOUBLE_EQ(uploadSpeed, speed);
}

// Negative
TEST_F(DownloadTest, setUploadSpeedNegative) {
	
	double uploadSpeed = -1;
	double originalSpeed = download->getStatistics().upload_speed;
	download->setUploadSpeed(uploadSpeed);
	double speed = download->getStatistics().upload_speed;
	EXPECT_DOUBLE_EQ(originalSpeed, speed);
}


/* Ratio */

//Trivial
TEST_F(DownloadTest, calcRatioTrivial) {
	
	double uploadAmount = 10;
	double downloadAmount = 5;
	double ratio = uploadAmount/downloadAmount;
	
	download->setUploadAmount(uploadAmount);
	download->setDownloadAmount(downloadAmount);
	download->calculateRatio();
	
	EXPECT_DOUBLE_EQ(ratio, download->getStatistics().ratio);
}

// Divide by zero
TEST_F(DownloadTest, calcRatioDLZero) {
	
	double uploadSpeed = 10;
	double downloadSpeed = 0;
	double ratio = 0;
	
	download->setUploadSpeed(uploadSpeed);
	download->setDownloadSpeed(downloadSpeed);
	download->calculateRatio();
	
	EXPECT_DOUBLE_EQ(ratio, download->getStatistics().ratio);
}

// UploadSpeed is zero
TEST_F(DownloadTest, calcRatioULZero) {
	
	double uploadSpeed = 0;
	double downloadSpeed = 10;
	double ratio = 0;
	
	download->setUploadSpeed(uploadSpeed);
	download->setDownloadSpeed(downloadSpeed);
	download->calculateRatio();
	
	EXPECT_DOUBLE_EQ(ratio, download->getStatistics().ratio);
}

/* Percentage */

// Trivial
TEST_F(DownloadTest, percentageTrivial) {
	
	double percentage = 45.6;
	download->setProgress(percentage);
	
	EXPECT_DOUBLE_EQ(percentage, download->getStatistics().download_percentage);
}

// Negative
TEST_F(DownloadTest, percentageNegative) {
	
	double originalPercentage = download->getStatistics().download_percentage;
	double percentage = -45.6;
	download->setProgress(percentage);
	
	EXPECT_DOUBLE_EQ(originalPercentage, download->getStatistics().download_percentage);
}

// Over 100
TEST_F(DownloadTest, percentageOver100) {
	
	double originalPercentage = download->getStatistics().download_percentage;
	double percentage = 154.3;
	download->setProgress(percentage);
	
	EXPECT_DOUBLE_EQ(originalPercentage, download->getStatistics().download_percentage);
}

/* Upload Amount */

// Trivial
TEST_F(DownloadTest, ULAmountTrivial){
	
	double uploadAmount = 45.6;
	download->setUploadAmount(uploadAmount);
	
	EXPECT_DOUBLE_EQ(uploadAmount, download->getStatistics().upload_amount);
}

// Negative
TEST_F(DownloadTest, ULAmountNegative){
	
	double originalULAmount = 10;
	download->setUploadAmount(originalULAmount);
	double uploadAmount = -45.6;
	download->setUploadAmount(uploadAmount);
	
	EXPECT_DOUBLE_EQ(originalULAmount, download->getStatistics().upload_amount);
}

/* Download Amount */

// Trivial
TEST_F(DownloadTest, DLAmountTrivial){
	
	double downloadAmount = 45.6;
	download->setDownloadAmount(downloadAmount);
	
	EXPECT_DOUBLE_EQ(downloadAmount, download->getStatistics().download_amount);
}

// Negative
TEST_F(DownloadTest, DLAmountNegative){
	
	double originalDLAmount = 10;
	download->setDownloadAmount(originalDLAmount);
	double downloadAmount = -45.6;
	download->setDownloadAmount(downloadAmount);
	
	EXPECT_DOUBLE_EQ(originalDLAmount, download->getStatistics().download_amount);
}

/* Seeders */

//Trivial
TEST_F(DownloadTest, seedersTrivial){
	
	int seeders = 5;
	download->setSeeders(seeders);
	
	EXPECT_EQ(seeders, download->getStatistics().seeders);
}

//Negative
TEST_F(DownloadTest, seedersNegative){
	
	int originalSeeders = 5;
	download->setSeeders(originalSeeders);
	int seeders = -1;
	download->setSeeders(seeders);
	
	EXPECT_EQ(originalSeeders, download->getStatistics().seeders);
}

/* Peers */

//Trivial
TEST_F(DownloadTest, peersTrivial){
	
	int peers = 5;
	download->setPeers(peers);
	
	EXPECT_EQ(peers, download->getStatistics().peers);
}

//Negative
TEST_F(DownloadTest, peersNegative){
	
	int originalPeers = 5;
	download->setPeers(originalPeers);
	int peers = -1;
	download->setPeers(peers);
	
	EXPECT_EQ(originalPeers, download->getStatistics().peers);
}

/***********************************
***** END DOWNLOAD STATS TESTS *****
***********************************/

/* Status */

// Trivial
TEST_F(DownloadTest, statusTrivial){
	
	download->setStatus(DOWNLOADING);
	EXPECT_EQ(DOWNLOADING, download->getStatus());
}

// Bad Status
TEST_F(DownloadTest, statusWrong){
	
	int status = download->getStatus();
	download->setStatus(-1);
	
	EXPECT_EQ(status, download->getStatus());
}

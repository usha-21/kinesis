#include "RotatingStaticCredentialProvider.h"
#include "Logger.h"
LOGGER_TAG("com.amazonaws.kinesis.video");

using namespace com::amazonaws::kinesis::video;

void RotatingStaticCredentialProvider::updateCredentials(Credentials &credentials) {
    // Copy the stored creds forward
    credentials = credentials_;

    // Update only the expiration
    auto now_time = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch());
    auto expiration_seconds = now_time + ROTATION_PERIOD;
    credentials.setExpiration(std::chrono::seconds(expiration_seconds.count()));
    LOG_INFO("New credentials expiration is " << credentials.getExpiration().count());
}

Header header


float64 GPSWeek

float64 GPSTime


#angular status

float64 yaw

float64 pitch

float64 roll






# Latitude [degrees]. Positive is north of equator; negative is south.
float64 latitude

# Longitude [degrees]. Positive is east of prime meridian; negative is west.
float64 longitude

# Altitude [m]. Positive is above the WGS 84 ellipsoid
# (quiet NaN if no altitude is available).
float64 altitude



float64 velocity_earth

float64 velocity_north


float64 velocity_up





float64 baseline




float64 NSV1

float64 NSV2



float64 Status


float64[9] position_covariance

float64[9] angular_covariance



uint8 position_covariance_type

uint8 angular_covariance_type
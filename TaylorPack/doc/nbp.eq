M1 = 1.98848 * 10.0^21.0;
G = 6.67408 * 10.0^(-11.0);
M2 = 5.97237 * 10.0^15.0;

diff(r1x, t) = v1x;
diff(r1y, t) = v1y;
diff(r1z, t) = v1z;

diff(r2x, t) = v2x;
diff(r2y, t) = v2y;
diff(r2z, t) = v2z;

diff(v1x, t) = G*M2 * (r2x - r1x) / abs((r2x - r1x)^3.0);
diff(v1y, t) = G*M2 * (r2y - r1y) / abs((r2y - r1y)^3.0);
diff(v1z, t) = G*M2 * (r2z - r1z) / abs((r2z - r1z)^3.0);

diff(v2x, t) = G*M1 * (r2x - r1x) / abs((r1x - r2x)^3.0);
diff(v2y, t) = G*M1 * (r2y - r1y) / abs((r1y - r2y)^3.0);
diff(v2z, t) = G*M1 * (r2z - r1z) / abs((r1z - r2z)^3.0);

initial_values= -1289359.131389, 435580.809773, 217346.339234, -56393719.986435, 125599283.627938, 54475540.715896, -0.005589, -0.013552, -0.005606, -28.101464, -10.359519, -4.491546;
start_time= 0.0;
stop_time = 10000.0;
step = 100.0;
absolute_error_tolerance = 0.1;
relative_error_tolerance = 0.1;

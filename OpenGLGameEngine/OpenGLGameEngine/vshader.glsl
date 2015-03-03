#version 330

uniform sampler2D texture;

uniform vec3 theta;
uniform vec3 trans;
uniform vec3 scale;
uniform vec3 eye;
uniform vec3 lookat;
uniform vec3 up;
uniform vec3 lightPosition;

uniform vec4 projection;

in vec2 vTexCoord;
in vec3 vPosition;
in vec3 vNormal;

out vec2 textureCoord;
out vec3 L;
out vec3 E;
out vec3 H;
out vec3 N;

void main()
{
	vec4 homogPos = vec4(vPosition, 1.0);

    // Compute the sines and cosines of each rotation
    // about each axis
    vec3 angles = radians (theta);
    vec3 c = cos (angles);
    vec3 s = sin (angles);

	vec3 nV = normalize(eye - lookat);
	vec3 u = normalize(cross(up, nV));
	vec3 v = cross(nV, u);
	
	float n = projection.x; 
	float f = projection.y;
	float w = projection.z;
	float h = projection.w;
	
	textureCoord = vTexCoord;
    
    // Rotation Matricies
    mat4 rx = mat4 (1.0,  0.0,  0.0,  0.0, 
                    0.0,  c.x,  s.x,  0.0,
                    0.0, -s.x,  c.x,  0.0,
                    0.0,  0.0,  0.0,  1.0);
                    
    mat4 ry = mat4 (c.y,  0.0, -s.y,  0.0, 
                    0.0,  1.0,  0.0,  0.0,
                    s.y,  0.0,  c.y,  0.0,
                    0.0,  0.0,  0.0,  1.0);

    mat4 rz = mat4 (c.z, -s.z,  0.0,  0.0, 
                    s.z,  c.z,  0.0,  0.0,
                    0.0,  0.0,  1.0,  0.0,
                    0.0,  0.0,  0.0,  1.0);

	// Translation Matrix
	mat4 transMat = mat4 (1.0,     0.0,     0.0,     0.0,
						  0.0,     1.0,     0.0,     0.0,
						  0.0,     0.0,     1.0,     0.0,
						  trans.x, trans.y, trans.z, 1.0);
    
	// Scaling Matrix
    mat4 scaleMat = mat4 (scale.x, 0.0,		0.0,	    0.0,
						  0.0,	   scale.y,	0.0,	    0.0,
						  0.0,	   0.0,	    scale.z,	0.0,
						  0.0,	   0.0,		0.0,	    1.0);

	// View Matrix
	mat4 viewMatrix = mat4 (u.x,          v.x,          nV.x,          0,
							u.y,          v.y,          nV.y,          0,
							u.z,          v.z,          nV.z,          0,
							dot(-u, eye), dot(-v, eye), dot(-nV, eye), 1);

	// Projection Matrix
	mat4 projectionMatrix = mat4((2.0 * n) / w,  0,          0,                    0,
								 0,              (2.0 * n)/h,  0,                    0,
								 0,              0,         -(f + n) / (f - n),   -1.0,
								 0,              0,         -(2.0 * f * n) / (f-n),  0);

    gl_Position = projectionMatrix * viewMatrix * transMat * rz * ry * rx * scaleMat * homogPos;

	// Shading 
	vec4 worldCoord4v = transMat * rz * ry * rx * scaleMat * homogPos;
	vec3 worldCoord3v = vec3 (worldCoord4v.x / worldCoord4v.w,
							  worldCoord4v.y / worldCoord4v.w,
							  worldCoord4v.z / worldCoord4v.w);

	vec4 worldNormal4v = rz * ry * rx * vec4(vNormal, 1.0);
	vec3 worldNormal3v = vec3 (worldNormal4v.x / worldNormal4v.w,
							   worldNormal4v.y / worldNormal4v.w,
							   worldNormal4v.z / worldNormal4v.w);

	L = normalize(lightPosition - worldCoord3v);
	E = normalize(eye - worldCoord3v);
	H = normalize(L + E);
	N = normalize(worldNormal3v);
}
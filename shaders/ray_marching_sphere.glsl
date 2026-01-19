#stage vertex
#version 330 core

// We do not need vertex attributes.
// gl_VertexID selects one of three hardcoded vertices.
out vec2 fragUV;

// Positions of a single fullscreen triangle in clip space
const vec2 FULLSCREEN_TRIANGLE[3] = vec2[](
    vec2(-1.0, -1.0),
    vec2(3.0, -1.0),
    vec2(-1.0, 3.0)
    );

void main()
{
    vec2 clipPos = FULLSCREEN_TRIANGLE[gl_VertexID];

    // Output directly in clip space
    gl_Position = vec4(clipPos, 0.0, 1.0);

    // Convert clip space to UV [0,1] (mostly for debugging)
    fragUV = clipPos * 0.5 + 0.5;
}


#stage fragment
#version 330 core
out vec4 FragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 uResolution; // add this (width,height)

// --- SDF sphere at origin in *object space* ---
float sdfSphere(vec3 p, float r) { return length(p) - r; }

// Scene in object space (so model moves it)
float sceneSDF_Object(vec3 pObj)
{
    // Sphere radius 1 at object origin
    return sdfSphere(pObj, 1.0);
}

vec3 estimateNormal_Object(vec3 pObj)
{
    float e = 0.001;
    float dx = sceneSDF_Object(pObj + vec3(e, 0, 0)) - sceneSDF_Object(pObj - vec3(e, 0, 0));
    float dy = sceneSDF_Object(pObj + vec3(0, e, 0)) - sceneSDF_Object(pObj - vec3(0, e, 0));
    float dz = sceneSDF_Object(pObj + vec3(0, 0, e)) - sceneSDF_Object(pObj - vec3(0, 0, e));
    return normalize(vec3(dx, dy, dz));
}

bool raymarch_ObjectSpace(vec3 rayOriginObj, vec3 rayDirObj, out vec3 hitObj)
{
    float t = 0.0;
    const float tMax = 100.0;
    const int maxSteps = 128;
    const float hitEps = 0.001;

    for (int i = 0; i < maxSteps; i++)
    {
        vec3 p = rayOriginObj + rayDirObj * t;
        float d = sceneSDF_Object(p);
        if (d < hitEps) { hitObj = p; return true; }
        t += d;
        if (t > tMax) break;
    }
    return false;
}

void main()
{
    // 1) Build inverse matrices *in shader*
    mat4 invProj = inverse(projection);
    mat4 invView = inverse(view);
    mat4 invModel = inverse(model);

    // 2) Camera position in world space from invView
    vec3 cameraPosWorld = (invView * vec4(0, 0, 0, 1)).xyz;

    // 3) Reconstruct a world-space ray direction for this pixel
    // Convert pixel -> NDC in [-1,1]
    vec2 ndc = (gl_FragCoord.xy / uResolution) * 2.0 - 1.0;

    // Points on near/far plane in view space (OpenGL NDC z is -1 near, +1 far)
    vec4 nearViewH = invProj * vec4(ndc, -1.0, 1.0);
    vec4 farViewH = invProj * vec4(ndc, 1.0, 1.0);
    vec3 nearView = nearViewH.xyz / nearViewH.w;
    vec3 farView = farViewH.xyz / farViewH.w;

    // Convert those view-space points to world space
    vec3 nearWorld = (invView * vec4(nearView, 1.0)).xyz;
    vec3 farWorld = (invView * vec4(farView, 1.0)).xyz;

	vec3 rayOriginWorld = vec3(0.0); // cameraPosWorld;
	vec3 rayDirWorld = vec3(0.0, 0.0, -1.0); //normalize(farWorld - nearWorld);

    // 4) Transform ray into OBJECT space (so SDF can stay in object coordinates)
    vec3 rayOriginObj = (invModel * vec4(rayOriginWorld, 1.0)).xyz;
    vec3 rayDirObj = normalize((invModel * vec4(rayDirWorld, 0.0)).xyz);

    // 5) March
    vec3 hitObj;
    if (!raymarch_ObjectSpace(rayOriginObj, rayDirObj, hitObj)) {
        FragColor = vec4(0.6, 0.8, 1.0, 1.0);
        return;
    }

    // 6) Shade (normal in object -> world for lighting)
    vec3 nObj = estimateNormal_Object(hitObj);
    vec3 nWorld = normalize((transpose(inverse(model)) * vec4(nObj, 0.0)).xyz);

    vec3 lightDirWorld = normalize(vec3(0.4, 1.0, 0.2));
    float diff = max(dot(nWorld, lightDirWorld), 0.0);

    vec3 color = vec3(1.0, 0.9, 0.8) * (0.15 + 0.85 * diff);
    FragColor = vec4(color, 1.0);
}

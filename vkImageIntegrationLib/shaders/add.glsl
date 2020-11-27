#version 450

layout(local_size_x = 1) in;

// The input tensors bind index is relative to index in parameter passed
layout(set = 0, binding = 0) buffer bina { float tina[]; };
layout(set = 0, binding = 1) buffer binb { float tinb[]; };
layout(set = 0, binding = 2) buffer bout { float tout[]; };

void main() {
	uint index = gl_GlobalInvocationID.x;
	tout[index] = tina[index] + tinb[index];
}

// ===============================================================================================================
// -*- C++ -*-
//
// Utility.cpp - Common code used by the application.
//
// Copyright (c) 2010 Guilherme R. Lampert
// guilherme.ronaldo.lampert@gmail.com
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// above is included in the resulting source code.
//
// ===============================================================================================================

#include "Utility.hpp"

// == Class Log ==

Log::Log(void) : m_pFile(NULL), m_open_flag(false)
{
#if defined (_DEBUG)
	Open("Program Debug Log.txt");
#endif // _DEBUG
}

bool Log::Open(const char * filename)
{
	Close();

	if ((m_pFile = fopen(filename, "wt")) != NULL)
	{
		m_open_flag = true;
	}

	return (m_open_flag);
}

void Log::Close(void)
{
	if (m_open_flag)
	{
		fflush(m_pFile);
		fclose(m_pFile);
		m_open_flag = false;
	}
}

void Log::Flush(void)
{
	fflush(m_pFile);
}

Log& Log::operator << (const std::string & text)
{
	if (m_open_flag)
		fputs(text.c_str(), m_pFile);

	return (*this);
}

Log& Log::operator << (const char * text)
{
	if (m_open_flag)
		fputs(text, m_pFile);

	return (*this);
}

Log& Log::operator << (char ch)
{
	if (m_open_flag)
		fprintf(m_pFile, "%c", ch);

	return (*this);
}

Log& Log::operator << (const void * ptr)
{
	if (m_open_flag)
		fprintf(m_pFile, "%p", ptr);

	return (*this);
}

Log& Log::operator << (short value)
{
	if (m_open_flag)
		fprintf(m_pFile, "%i", value);

	return (*this);
}

Log& Log::operator << (unsigned short value)
{
	if (m_open_flag)
		fprintf(m_pFile, "%u", value);

	return (*this);
}

Log& Log::operator << (int value)
{
	if (m_open_flag)
		fprintf(m_pFile, "%i", value);

	return (*this);
}

Log& Log::operator << (unsigned int value)
{
	if (m_open_flag)
		fprintf(m_pFile, "%u", value);

	return (*this);
}

Log& Log::operator << (float value)
{
	if (m_open_flag)
		fprintf(m_pFile, "%f", value);

	return (*this);
}

Log& Log::operator << (double value)
{
	if (m_open_flag)
		fprintf(m_pFile, "%lf", value);

	return (*this);
}

Log::~Log(void)
{
	Close();
}

// == Class MemoryBuffer ==

MemoryBuffer::MemoryBuffer(void)
: m_size(0), m_position(0), m_stream(NULL), m_end_of_stream(true), m_self_release(false)
{
}

MemoryBuffer::MemoryBuffer(unsigned int size, bool self_release)
: m_size(0), m_position(0), m_stream(NULL), m_end_of_stream(true), m_self_release(false)
{
	Allocate(size, self_release);
}

bool MemoryBuffer::Allocate(unsigned int size, bool self_release)
{
	if (size > 0)
	{
		// If m_stream is NULL, realloc() will behave like malloc().
		m_stream = realloc(m_stream, size);
		if (!m_stream)
		{
			LOG_ERROR("MemoryBuffer out of memory !");
			return (false);
		}

		m_size = size;
		m_position = 0;
		m_end_of_stream = false;
		m_self_release = self_release;

		return (true);
	}

	return (false);
}

int MemoryBuffer::ReadChar(void)
{
	if ((m_end_of_stream == false) && (m_stream != NULL))
	{
		m_position++;

		if (m_position == m_size)
			m_end_of_stream = true;

		return (*((char *)m_stream + (m_position - 1)));
	}
	else return (-1);
}

char * MemoryBuffer::ReadLine(char * buffer, unsigned int count)
{
	char * pointer = buffer;
	int ch;

	if ((buffer == NULL) || (count == 0))
	{
		return (NULL);
	}

	while (--count)
	{
		if ((ch = ReadChar()) == -1)
		{
			if (pointer == buffer)
			{
				return (NULL);
			}
			break;
		}

		if ((*pointer++ = (char)ch) == '\n')
			break;
	}

	*pointer = '\0';

	return (buffer);
}

int MemoryBuffer::Seek(long offset, int origin)
{
	unsigned int new_position = m_position;

	if (offset >= 0)
	{
		switch (origin)
		{
		case SEEK_SET:
			new_position = offset;
			break;

		case SEEK_CUR:
			new_position += offset;
			break;

		case SEEK_END:
			new_position = (m_size + offset);
			break;

		default:
			new_position = 0;
			break;
		}

		m_position = new_position;
		m_end_of_stream = ((m_position == m_size) ? true : false);
	}

	return (new_position);
}

void MemoryBuffer::Free(void)
{
	if (m_stream)
	{
		free(m_stream);
		m_stream = NULL;
	}

	m_size = 0;
	m_position = 0;
	m_end_of_stream = true;
}

bool MemoryBuffer::Eof(void) const
{
	return (m_end_of_stream);
}

void * MemoryBuffer::GetBufferPointer(void) const
{
	return (m_stream);
}

MemoryBuffer::~MemoryBuffer(void)
{
	if (m_self_release)
	{
		Free();
	}
}

// == Utility Functions ==

void glBegin2D(int window_width, int window_height)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	glOrtho(0.0, static_cast<double>(window_width), 0.0, static_cast<double>(window_height), -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void glEnd2D(void)
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

int glPrintf(int x, int y, const char * format, ...)
{
	char buffer[2048];
	va_list arg_list;
	int nCount;

	va_start(arg_list, format);
	nCount = vsnprintf(buffer, sizeof(buffer), format, arg_list);
	va_end(arg_list);

	glRasterPos2i(x, y);

	for (int i = 0; i < nCount; i++)
	{
		////glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
	}

	return (nCount);
}

int CalcFPS(void)
{
	static int ret = 0;
	static float fps = 0.0f;
	static float last_time = 0.0f;
	////float current_time = static_cast<float>((glutGet(GLUT_ELAPSED_TIME) * 0.001f));
	float current_time = 0.0f;

	fps++;

	if ((current_time - last_time) > 1.0f)
    {
		last_time = current_time;
		ret = static_cast<int>(fps);
		fps = 0.0f;
	}

	return (ret);
}

unsigned char * LoadUncompressedTGA(const char * fileName, int & width, int & height, int & bytesPerPixel)
{
	FILE * fp;
	short int depth = 0;
	short int w = 0, h = 0;
	unsigned char * data;

	// Open the file in binary mode.
	fp = fopen(fileName, "rb");

	// Problem opening file?
	if (fp == NULL)
	{
		LOG_ERROR("Problem opening TGA file: " << fileName);
		return (NULL);
	}
	else
	{
		// Load information about the tga, aka the header:

		// Seek to the width.
		fseek(fp, 12, SEEK_SET);
		fread(&w, sizeof(short int), 1, fp);

		// Seek to the height.
		fseek(fp, 14, SEEK_SET);
		fread(&h, sizeof(short int), 1, fp);

		// Seek to the depth.
		fseek(fp, 16, SEEK_SET);
		fread(&depth, sizeof(unsigned char), 1, fp);

		// Load the actual image data:

		// Total bytes = h * w * components per pixel.
		const int t = h * w * (depth / 8);

		// Allocate memory for the image data.
		data = (unsigned char *)malloc(sizeof(unsigned char) * t);
		if (!data)
		{
			LOG_ERROR("Out of memory for image loading!");
			fclose(fp);
			return (NULL);
		}

		// Seek to the image data.
		fseek(fp, 18, SEEK_SET);
		fread(data, sizeof(unsigned char), t, fp);

		// We're done reading.
		fclose(fp);

		LOG_INFO("Loaded TGA image: " << fileName << " w = " << w << " h = " << h);

		// Fill The Image Info:
		width  = w;
		height = h;
		bytesPerPixel = (depth / 8);

		return (data);
	}
}

const char * OpenFileDialog(void * hwnd, int mode, const char * filter, const char * ext)
{
#ifdef _WIN32
	// Window version has a nice file selection dialog box
	BOOL result;
	int index = 0;

	static char full_file_name[MAX_PATH];
	memset(full_file_name, 0, sizeof(full_file_name));

	char sorted_filter[MAX_PATH];
	memset(sorted_filter, 0, sizeof(sorted_filter));

	OPENFILENAME open_params;
	memset(&open_params, 0, sizeof(OPENFILENAME));

repeat:

	while ((*filter != ',') && (*filter != '\0'))
	{
		sorted_filter[index] = *filter;
		index++;
		filter++;
	}

	index++;

	while ((*ext != ',') && (*ext != '\0'))
	{
		sorted_filter[index] = *ext;
		index++;
		ext++;
	}

	index++;

	if ((*filter == ',') || (*ext == ','))
	{
		filter++;
		ext++;
		goto repeat;
	}

	open_params.lStructSize = sizeof(OPENFILENAME);
	open_params.hwndOwner = (HWND)hwnd;
	open_params.lpstrFilter = (LPCSTR)sorted_filter;
	open_params.lpstrFile = (LPSTR)full_file_name;
	open_params.nMaxFile = MAX_PATH;
	open_params.Flags = (OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY);

	if (mode == SAVE_FILE)
	{
		result = GetSaveFileName(&open_params);
	}
	else if (mode == OPEN_FILE)
	{
		result = GetOpenFileName(&open_params);
	}
	else
	{
		result = FALSE;
	}

	return ((result == FALSE) ? NULL : full_file_name);
#else
	// Well, well, I'm a bit lazy today so I'll just ask for
	// the Linux and Mac users to type the file name in the console :P
	static std::string path;
	path.clear();

	system("clear");
	std::cout << "#=========================================#" << std::endl;
	std::cout << "#         Wavefront Object Viewer         #" << std::endl;
	std::cout << "#=========================================#" << std::endl;
	std::cout << std::endl;
	std::cout << "Please type the OBJ file path and name" << std::endl;
	std::cout << "relative to the current directory.    " << std::endl;
	std::cout << "Example: samples/Cow.obj              " << std::endl;
	std::cout << std::endl;
	std::cin >> path;
	std::cout << std::endl;

	return (path.c_str());
#endif
}

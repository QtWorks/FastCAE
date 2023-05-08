# -------关联C++库---------------
import MainWindow
import ctypes
import platform
from ctypes import *
system = platform.system()
if system == "Windows":
    pre = "./"
    suff = ".dll"
else:
    pre = "../lib/lib"
    suff = ".so"

libfile = ctypes.cdll.LoadLibrary
filename = pre+"PostInterface"+suff
process = libfile(filename)

# ---------------------------------

# -------定义函数------------------


def script_openFile(id, type, file):
    MainWindow.script_openFile(id, type, file)
    pass


def script_applyClicked(id, type):
    MainWindow.script_applyClicked(id, type)
    pass


def script_Properties_Opacity(id, type, obj_id, mOpacity):
    MainWindow.script_Properties_Opacity(id, type, obj_id, mOpacity)
    pass


def script_Properties_colorColumn(id, type, obj_id, mColorColumnStyle):
    MainWindow.script_Properties_colorColumn(
        id, type, obj_id, mColorColumnStyle)
    pass


def script_Properties_scalarBarTitle(id, type, obj_id, colName, m_title):
    MainWindow.script_Properties_scalarBarTitle(
        id, type, obj_id, colName, m_title)
    pass


def script_Properties_scalarBarFontSize(id, type, obj_id, colName, m_fontSize):
    MainWindow.script_Properties_scalarBarFontSize(
        id, type, obj_id, colName, m_fontSize)
    pass


def script_Properties_scalarBarNumLables(id, type, obj_id, colName, m_numLables):
    MainWindow.script_Properties_scalarBarNumLables(
        id, type, obj_id, colName, m_numLables)
    pass


def script_Properties_lineWidth(id, type, obj_id, mLineWidth):
    MainWindow.script_Properties_lineWidth(id, type, obj_id, mLineWidth)
    pass


def script_Properties_pointSize(id, type, obj_id, mPointSize):
    MainWindow.script_Properties_pointSize(id, type, obj_id, mPointSize)
    pass


def script_Properties_translate(id, type, obj_id, x, y, z):
    MainWindow.script_Properties_translate(id, type, obj_id, x, y, z)
    pass


def script_Properties_origin(id, type, obj_id, x, y, z):
    MainWindow.script_Properties_origin(id, type, obj_id, x, y, z)
    pass


def script_Properties_scale(id, type, obj_id, x, y, z):
    MainWindow.script_Properties_scale(id, type, obj_id, x, y, z)
    pass


def script_Properties_orientation(id, type, obj_id, x, y, z):
    MainWindow.script_Properties_orientation(id, type, obj_id, x, y, z)
    pass


def script_Properties_representation(id, type, obj_id, m_enum_representationtype):
    MainWindow.script_Properties_representation(
        id, type, obj_id, m_enum_representationtype)
    pass


def script_Properties_specular(id, type, obj_id, mSpecular):
    MainWindow.script_Properties_specular(id, type, obj_id, mSpecular)
    pass


def script_Properties_diffuse(id, type, obj_id, mDiffuse):
    MainWindow.script_Properties_diffuse(id, type, obj_id, mDiffuse)
    pass


def script_Properties_ambient(id, type, obj_id, mAmbient):
    MainWindow.script_Properties_ambient(id, type, obj_id, mAmbient)
    pass


def script_Properties_specularPower(id, type, obj_id, mSpecularPower):
    MainWindow.script_Properties_specularPower(
        id, type, obj_id, mSpecularPower)
    pass


def script_Properties_specularColor(id, type, obj_id, r, g, b):
    MainWindow.script_Properties_specularColor(id, type, obj_id, r, g, b)
    pass


def script_Properties_solidColor(id, type, obj_id, r, g, b):
    MainWindow.script_Properties_solidColor(id, type, obj_id, r, g, b)
    pass


def script_Properties_edgeColor(id, type, obj_id, r, g, b):
    MainWindow.script_Properties_edgeColor(id, type, obj_id, r, g, b)
    pass


def script_Properties_interpolation(id, type, obj_id, m_enum_interpolationtype):
    MainWindow.script_Properties_interpolation(
        id, type, obj_id, m_enum_interpolationtype)
    pass


def script_Properties_Flag_scalarBar(id, type, obj_id, mColorColumnStyle):
    MainWindow.script_Properties_Flag_scalarBar(
        id, type, obj_id, mColorColumnStyle)
    pass


def script_Properties_EnableOpacityMap(id, type, obj_id, val):
    MainWindow.script_Properties_EnableOpacityMap(id, type, obj_id, val)
    pass


def script_Properties_visible(id, type, obj_id, flag_show_actors):
    MainWindow.script_Properties_visible(id, type, obj_id, flag_show_actors)
    pass


def script_Properties_show_scalarBars(id, type, obj_id, mScalarBarVisible):
    MainWindow.script_Properties_show_scalarBars(
        id, type, obj_id, mScalarBarVisible)
    pass


def script_Properties_show_cubeAxes(id, type, obj_id, flag_cubeAxes):
    MainWindow.script_Properties_show_cubeAxes(id, type, obj_id, flag_cubeAxes)
    pass


def script_Properties_scalarBarPosition(id, type, obj_id, colName, tep_orietation, pos0, pos1, pos2, pos3):
    MainWindow.script_Properties_scalarBarPosition(
        id, type, obj_id, colName, tep_orietation, pos0, pos1, pos2, pos3)
    pass


def script_Clip(id, type, obj_id):
    MainWindow.script_FilterClip(id, type, obj_id)
    pass


def script_Slice(id, type, obj_id):
    MainWindow.script_FilterSlice(id, type, obj_id)
    pass


def script_Contour(id, type, obj_id):
    MainWindow.script_FilterContour(id, type, obj_id)
    pass


def script_Vector(id, type, obj_id):
    MainWindow.script_FilterVector(id, type, obj_id)
    pass


def script_Reflection(id, type, obj_id):
    MainWindow.script_FilterReflection(id, type, obj_id)
    pass


def script_Smooth(id, type, obj_id):
    MainWindow.script_FilterSmooth(id, type, obj_id)
    pass


def script_StreamLine(id, type, obj_id):
    MainWindow.script_FilterStreamLine(id, type, obj_id)
    pass

###################


def script_Vector_GlyphVector(id, type, obj_id, val):
    MainWindow.script_Properties_vector_GlyphVector(id, type, obj_id, val)
    pass


def script_Vector_scalar(id, type, obj_id, val):
    MainWindow.script_Properties_vector_scalar(id, type, obj_id, val)
    pass


def script_Vector_normal(id, type, obj_id, val):
    MainWindow.script_Properties_vector_normal(id, type, obj_id, val)
    pass


def script_Vector_numPoints(id, type, obj_id, val):
    MainWindow.script_Properties_vector_numPoints(id, type, obj_id, val)
    pass


def script_Vector_glyph_type(id, type, obj_id, val):
    MainWindow.script_Properties_vector_glyph_type(id, type, obj_id, val)
    pass


def script_Vector_glyph_tipRes(id, type, obj_id, val):
    MainWindow.script_Properties_vector_glyph_tipRes(id, type, obj_id, val)
    pass


def script_Vector_glyph_tipRad(id, type, obj_id, val):
    MainWindow.script_Properties_vector_glyph_tipRad(id, type, obj_id, val)
    pass


def script_Vector_glyph_tipLen(id, type, obj_id, val):
    MainWindow.script_Properties_vector_glyph_tipLen(id, type, obj_id, val)
    pass


def script_FilterStreamLine(id, type, obj_id):
    MainWindow.script_FilterStreamLine(id, type, obj_id)
    pass


def script_Vector_glyph_shaftRes(id, type, obj_id, val):
    MainWindow.script_Properties_vector_glyph_shaftRes(id, type, obj_id, val)
    pass


def script_Vector_glyph_shaftRad(id, type, obj_id, val):
    MainWindow.script_Properties_vector_glyph_shaftRad(id, type, obj_id, val)
    pass


def script_Properties_view_backgroundType(id, type, obj_id, val):
    MainWindow.script_Properties_view_backgroundType(id, type, obj_id, val)
    pass


def script_Properties_view_backgroundColor(id, type, obj_id, red, green, blue):
    MainWindow.script_Properties_view_backgroundColor(
        id, type, obj_id, red, green, blue)
    pass


def script_Properties_view_background2Color(id, type, obj_id, red, green, blue):
    MainWindow.script_Properties_view_background2Color(
        id, type, obj_id, red, green, blue)
    pass


def script_Properties_view_axesVisible(id, type, a):
    MainWindow.script_Properties_view_axesVisible(id, type, a)
    pass


def script_Properties_view_cameraParallel(id, type, a):
    MainWindow.script_Properties_view_cameraParallel(id, type, a)
    pass


def script_Properties_view_interaction(id, type, a):
    MainWindow.script_Properties_view_interaction(id, type, a)
    pass


def script_Properties_renderView(id, type):
    MainWindow.script_Properties_renderView(id, type)
    pass


def script_Camera_Position(id, type, pos0, pos1, pos2):
    MainWindow.script_Camera_Position(id, type, pos0, pos1, pos2)
    pass


def script_Camera_FocalPoint(id, type, focalPoint0, focalPoint1, focalPoint2):
    MainWindow.script_Camera_FocalPoint(
        id, type, focalPoint0, focalPoint1, focalPoint2)
    pass


def script_Camera_ClippingRange(id, type, clippingRange0, clippingRange1):
    MainWindow.script_Camera_ClippingRange(
        id, type, clippingRange0, clippingRange1)
    pass


def script_Camera_ViewUp(id, type, viewup0, viewup1, viewup2):
    MainWindow.script_Camera_ViewUp(id, type, viewup0, viewup1, viewup2)
    pass


def script_Camera_ViewAngle(id, type, angle):
    MainWindow.script_Camera_ViewAngle(id, type, angle)
    pass


def script_Camera_Zoom(id, type, zoom):
    MainWindow.script_Camera_Zoom(id, type, zoom)
    pass


def script_Camera_Reset(id, type,):
    MainWindow.script_Camera_Reset(id, type,)
    pass


def script_Properties_planeOrigin(id, type, obj_id, x, y, z):
    MainWindow.script_Properties_planeOrigin(id, type, obj_id, x, y, z)
    pass


def script_Properties_planeNormal(id, type, obj_id, x, y, z):
    MainWindow.script_Properties_planeNormal(id, type, obj_id, x, y, z)
    pass


def script_Properties_planeVisible(id, type, obj_id, a):
    MainWindow.script_Properties_planeVisible(id, type, obj_id, a)
    pass


def script_Properties_insideOut(id, type, obj_id, a):
    MainWindow.script_Properties_insideOut(id, type, obj_id, a)
    pass


def script_Contour_Column(id, type, obj_id, val):
    MainWindow.script_Properties_contourColumn(id, type, obj_id, val)
    pass


def script_Contour_value(id, type, obj_id, val):
    MainWindow.script_Properties_contourValue(id, type, obj_id, val)
    pass


def script_Contour_reflection(id, type, obj_id, aaa):
    MainWindow.script_Properties_contour_reflection(id, type, obj_id, aaa)
    pass


def script_Contour_reflectionAxes(id, type, obj_id, val):
    MainWindow.script_Properties_contour_reflectionAxes(id, type, obj_id, val)
    pass


def script_Properties_reflectionAxes(id, type, obj_id, reflection_axis):
    MainWindow.script_Properties_reflectionAxes(
        id, type, obj_id, reflection_axis)
    pass


def Smooth_smooth(id, type, obj_id, smotype, coef):
    MainWindow.script_Properties_smooth(id, type, obj_id, smotype, coef)
    pass


def script_Streamline_vector(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_vector(id, type, obj_id, val)
    pass


def script_Streamline_integration_type(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_integration_type(
        id, type, obj_id, val)
    pass


def script_Streamline_integration_direction(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_integration_direction(
        id, type, obj_id, val)
    pass


def script_Streamline_integration_stepUnit(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_integration_type(
        id, type, obj_id, val)
    pass


def script_Properties_streamline_integration_stepUnit(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_integration_stepUnit(
        id, type, obj_id, val)
    pass


def script_Streamline_integration_initStepLen(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_integration_initStepLen(
        id, type, obj_id, val)
    pass


def script_Streamline_integration_miniStepLen(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_integration_miniStepLen(
        id, type, obj_id, val)
    pass


def script_Streamline_integration_maxiStepLen(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_integration_maxiStepLen(
        id, type, obj_id, val)
    pass


def script_Streamline_stream_maxiSteps(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_stream_maxiSteps(
        id, type, obj_id, val)
    pass


def script_Streamline_stream_maxiStreamLen(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_stream_maxiStreamLen(
        id, type, obj_id, val)
    pass
   ###########


def script_Streamline_stream_terminalSpeed(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_stream_terminalSpeed(
        id, type, obj_id, val)
    pass


def script_Streamline_stream_maxiError(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_stream_maxiError(
        id, type, obj_id, val)
    pass


def script_Streamline_seeds_type(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_seeds_type(id, type, obj_id, val)
    pass


def script_Streamline_seeds_mPoint(id, type, obj_id, val0, val1, val2):
    MainWindow.script_Properties_streamline_seeds_mPoint(
        id, type, obj_id, val0, val1, val2)
    pass


def script_Streamline_seeds_num_points(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_seeds_num_points(
        id, type, obj_id, val)
    pass


def script_Streamline_seeds_radius(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_seeds_radius(id, type, obj_id, val)
    pass


def script_Streamline_vorticity(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_vorticity(id, type, obj_id, val)
    pass


def script_Streamline_interpolatorType(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_interpolatorType(
        id, type, obj_id, val)
    pass


def script_Streamline_surface_streamLines(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_surface_streamLines(
        id, type, obj_id, val)
    pass


def script_Properties_streamline_reflection(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_reflection(id, type, obj_id, val)
    pass


def script_Properties_streamline_reflectionAxes(id, type, obj_id, val):
    MainWindow.script_Properties_streamline_reflectionAxes(
        id, type, obj_id, val)
    pass


# ---------------------------------
# -------后处理最新定义------------
# -------定义函数------------------
def openPostFile(id, type, file):
    stype = bytes(type, encoding='utf-8')
    sfile = bytes(file, encoding='utf-8')
    process.openPostFile(id, stype, sfile)
    pass


def setDisplayMode(id, type):
    process.setDisplayMode(id, type)
    pass


def savePostImage(id, file):
    sfile = bytes(file, encoding='utf-8')
    process.savePostImage(id, sfile)
    pass


def savePostAnimation(id, file, fps):
    sfile = bytes(file, encoding='utf-8')
    process.savePostAnimation(id, sfile, fps)
    pass


def runAnimation(id, index):
    process.runAnimation(id, index)
    pass


def stopAnimation(id, index):
    process.stopAnimation(id, index)
    pass


def firstFrame(id):
    process.firstFrame(id)
    pass


def proviousFrame(id):
    process.proviousFrame(id)
    pass


def nextFrame(id):
    process.nextFrame(id)
    pass


def lastFrame(id):
    process.lastFrame(id)
    pass


class Clip:
    def __init__(self):
        self.blocks = dict()
        self.blockStr = ""

    def setParentID(self, id):
        self.pID = id

    def setName(self, name):
        self.name = name

    def setOrigin(self, xOri, yOri, zOri):
        self.xOri = xOri
        self.yOri = yOri
        self.zOri = zOri

    def setNormal(self, xNor, yNor, zNor):
        self.xNor = xNor
        self.yNor = yNor
        self.zNor = zNor

    def setInsideOut(self, io):
        self.io = io

    def setID(self, id):
        self.id = id

    def appendBlock(self, pID, index):
        self.blocks.setdefault(pID, set()).add(index)

        pidList = self.blocks.keys()
        sblock = ""
        for parent in pidList:
            strBlock = ""
            blockList = self.blocks.get(parent)
            for blockID in blockList:
                strBlock = strBlock + str(blockID) + ","
            strBlock = str(parent) + ":" + strBlock[:-1]
            sblock = sblock + strBlock + ';'
        sblock = sblock[:-1]
        self.blockStr = bytes(sblock, encoding='utf-8')

    def create(self):
        sname = bytes(self.name, encoding='utf-8')
        process.createClip(c_int(self.pID), self.blockStr, sname, c_double(self.xOri), c_double(self.yOri), c_double(self.zOri),
                           c_double(self.xNor), c_double(self.yNor), c_double(self.zNor), c_bool(self.io))
        del self

    def edit(self):
        sname = bytes(self.name, encoding='utf-8')
        process.editClip(c_int(self.id), self.blockStr, sname, c_double(self.xOri), c_double(self.yOri), c_double(self.zOri),
                         c_double(self.xNor), c_double(self.yNor), c_double(self.zNor), c_bool(self.io))
        del self


class Slice:
    def __init__(self):
        self.blocks = dict()

    def setParentID(self, id):
        self.pID = id

    def setName(self, name):
        self.name = name

    def setOrigin(self, xOri, yOri, zOri):
        self.xOri = xOri
        self.yOri = yOri
        self.zOri = zOri

    def setNormal(self, xNor, yNor, zNor):
        self.xNor = xNor
        self.yNor = yNor
        self.zNor = zNor

    def setID(self, id):
        self.id = id

    def appendBlock(self, pID, index):
        self.blocks.setdefault(pID, set()).add(index)

        pidList = self.blocks.keys()
        sblock = ""
        for parent in pidList:
            strBlock = ""
            blockList = self.blocks.get(parent)
            for blockID in blockList:
                strBlock = strBlock + str(blockID) + ","
            strBlock = str(parent) + ":" + strBlock[:-1]
            sblock = sblock + strBlock + ';'
        sblock = sblock[:-1]
        self.blockStr = bytes(sblock, encoding='utf-8')

    def create(self):
        sname = bytes(self.name, encoding='utf-8')
        process.createSlice(c_int(self.pID), self.blockStr, sname, c_double(self.xOri), c_double(self.yOri), c_double(self.zOri),
                            c_double(self.xNor), c_double(self.yNor), c_double(self.zNor))
        del self

    def edit(self):
        sname = bytes(self.name, encoding='utf-8')
        process.editSlice(c_int(self.id), self.blockStr, sname, c_double(self.xOri), c_double(self.yOri), c_double(self.zOri),
                          c_double(self.xNor), c_double(self.yNor), c_double(self.zNor))
        del self


class ISOSurface:
    def __init__(self):
        self.blocks = dict()
        self.values = list()

    def setParentID(self, id):
        self.pID = id

    def setName(self, name):
        self.name = name

    def setVariable(self, var):
        self.variable = var

    def appendValue(self, val):
        self.values.append(val)

    def appendBlock(self, pID, index):
        self.blocks.setdefault(pID, set()).add(index)

    def create(self):
        pidList = self.blocks.keys()
        sblock = ""
        for parent in pidList:
            strBlock = ""
            blockList = self.blocks.get(parent)
            for blockID in blockList:
                strBlock = strBlock + str(blockID) + ","
            strBlock = str(parent) + ":" + strBlock[:-1]
            sblock = sblock + strBlock + ';'
        sblock = sblock[:-1]
        blockStr = bytes(sblock, encoding='utf-8')

        svalue = ""
        for value in self.values:
            svalue = svalue + str(value) + ","
        svalue = svalue[:-1]
        valueStr = bytes(svalue, encoding='utf-8')
        variableStr = bytes(self.variable, encoding='utf-8')
        sname = bytes(self.name, encoding='utf-8')
        process.createISOSurface(
            c_int(self.pID), blockStr, sname, variableStr, valueStr)
        del self


class ISOCurve:
    def __init__(self):
        self.blocks = dict()
        self.values = list()

    def setParentID(self, id):
        self.pID = id

    def setName(self, name):
        self.name = name

    def setVariable(self, var):
        self.variable = var

    def appendValue(self, val):
        self.values.append(val)

    def appendBlock(self, pID, index):
        self.blocks.setdefault(pID, set()).add(index)

    def create(self):
        pidList = self.blocks.keys()
        sblock = ""
        for parent in pidList:
            strBlock = ""
            blockList = self.blocks.get(parent)
            for blockID in blockList:
                strBlock = strBlock + str(blockID) + ","
            strBlock = str(parent) + ":" + strBlock[:-1]
            sblock = sblock + strBlock + ';'
        sblock = sblock[:-1]
        blockStr = bytes(sblock, encoding='utf-8')

        svalue = ""
        for value in self.values:
            svalue = svalue + str(value) + ","
        svalue = svalue[:-1]
        valueStr = bytes(svalue, encoding='utf-8')
        variableStr = bytes(self.variable, encoding='utf-8')
        sname = bytes(self.name, encoding='utf-8')
        process.createISOCurve(c_int(self.pID), blockStr,
                               sname, variableStr, valueStr)
        del self


class Vector:
    def __init__(self):
        self.blocks = dict()

    def setParentID(self, id):
        self.pID = id

    def setName(self, name):
        self.name = name

    def setVectorName(self, name):
        self.vectorName = name

    def setMaxNumber(self, num):
        self.maxNum = num

    def setScaleMode(self, mode):
        self.mode = mode

    def setScaleFactor(self, factor):
        self.factor = factor

    def setUsePointData(self, ispoint):
        self.isPoint = ispoint

    def appendBlock(self, pID, index):
        self.blocks.setdefault(pID, set()).add(index)

    def create(self):
        pidList = self.blocks.keys()
        sblock = ""
        for parent in pidList:
            strBlock = ""
            blockList = self.blocks.get(parent)
            for blockID in blockList:
                strBlock = strBlock + str(blockID) + ","
            strBlock = str(parent) + ":" + strBlock[:-1]
            sblock = sblock + strBlock + ';'
        sblock = sblock[:-1]
        blockStr = bytes(sblock, encoding='utf-8')
        svector = bytes(self.vectorName, encoding='utf-8')
        sname = bytes(self.name, encoding='utf-8')
        process.createVector(c_int(self.pID), blockStr, sname, svector, c_int(self.maxNum),
                             c_int(self.mode), c_double(self.factor), c_bool(self.isPoint))
        del self


class StreamLine:
    def __init__(self):
        self.blocks = dict()

    def setParentID(self, id):
        self.pID = id

    def setName(self, name):
        self.name = name

    def setVectorName(self, name):
        self.vectorName = name

    def setStartPoint(self, x, y, z):
        self.xStart = x
        self.yStart = y
        self.zStart = z

    def setEndPoint(self, x, y, z):
        self.xEnd = x
        self.yEnd = y
        self.zEnd = z

    def setUsePointData(self, ispoint):
        self.isPoint = ispoint

    def setSeedCount(self, seeds):
        self.seeds = seeds

    def setMaxLength(self, length):
        self.length = length

    def setInitStep(self, step):
        self.initStep = step

    def setMinStep(self, step):
        self.minStep = step

    def setMaxStep(self, step):
        self.maxStep = step

    def setStepNumber(self, num):
        self.stepNum = num

    def setDirection(self, d):
        self.dire = d

    def appendBlock(self, pID, index):
        self.blocks.setdefault(pID, set()).add(index)

    def create(self):
        pidList = self.blocks.keys()
        sblock = ""
        for parent in pidList:
            strBlock = ""
            blockList = self.blocks.get(parent)
            for blockID in blockList:
                strBlock = strBlock + str(blockID) + ","
            strBlock = str(parent) + ":" + strBlock[:-1]
            sblock = sblock + strBlock + ';'
        sblock = sblock[:-1]
        blockStr = bytes(sblock, encoding='utf-8')
        svector = bytes(self.vectorName, encoding='utf-8')
        sname = bytes(self.name, encoding='utf-8')
        process.createStreamLine(c_int(self.pID), blockStr, sname, svector, c_double(self.xStart), c_double(self.yStart),
                                 c_double(self.zStart), c_double(self.xEnd), c_double(
                                     self.yEnd), c_double(self.zEnd),
                                 c_int(self.seeds), c_double(self.length), c_double(
                                     self.initStep), c_double(self.minStep),
                                 c_double(self.maxStep), c_int(self.stepNum), c_int(self.dire), c_bool(self.isPoint))
        del self


class Calculate:
    def __init__(self):
        self.blocks = dict()
        self.scalars = list()
        self.vectors = list()

    def setParentID(self, id):
        self.pID = id

    def setName(self, name):
        self.name = name

    def setFunction(self, func):
        self.function = func

    def appendScalar(self, scalar):
        self.scalars.append(scalar)

    def appendVector(self, vector):
        self.vectors.append(vector)

    def setUsePointData(self, ispoint):
        self.isPoint = ispoint

    def appendBlock(self, pID, index):
        self.blocks.setdefault(pID, set()).add(index)

    def create(self):
        pidList = self.blocks.keys()
        sblock = ""
        for parent in pidList:
            strBlock = ""
            blockList = self.blocks.get(parent)
            for blockID in blockList:
                strBlock = strBlock + str(blockID) + ","
            strBlock = str(parent) + ":" + strBlock[:-1]
            sblock = sblock + strBlock + ';'
        sblock = sblock[:-1]
        blockStr = bytes(sblock, encoding='utf-8')
        sScalar = ""
        for scalar in self.scalars:
            sScalar = sScalar + str(scalar) + ","
        sScalar = sScalar[:-1]
        svector = ""
        for vector in self.vectors:
            svector = svector + str(vector) + ","
        svector = svector[:-1]
        scalarStr = bytes(sScalar, encoding='utf-8')
        vectorStr = bytes(svector, encoding='utf-8')
        funcStr = bytes(self.function, encoding='utf-8')
        sname = bytes(self.name, encoding='utf-8')
        process.createCalaulate(c_int(
            self.pID), blockStr, sname, funcStr, scalarStr, vectorStr, c_bool(self.isPoint))
        del self


class Reflection:
    def __init__(self):
        self.blocks = dict()

    def setParentID(self, id):
        self.pID = id

    def setName(self, name):
        self.name = name

    def setCenter(self, center):
        self.center = center

    def setPlane(self, plane):
        self.plane = plane

    def appendBlock(self, pID, index):
        self.blocks.setdefault(pID, set()).add(index)

    def create(self):
        pidList = self.blocks.keys()
        sblock = ""
        for parent in pidList:
            strBlock = ""
            blockList = self.blocks.get(parent)
            for blockID in blockList:
                strBlock = strBlock + str(blockID) + ","
            strBlock = str(parent) + ":" + strBlock[:-1]
            sblock = sblock + strBlock + ';'
        sblock = sblock[:-1]
        blockStr = bytes(sblock, encoding='utf-8')

        sname = bytes(self.name, encoding='utf-8')
        process.createReflection(c_int(self.pID), blockStr, sname, c_int(
            self.plane), c_double(self.center))
        del self


class VariableColor:
    def __init__(self):
        self.blocks = dict()
        self.isVariable = False
        self.red = 1.0
        self.green = 1.0
        self.blue = 1.0
        self.type = 0
        self.vName = ""
        self.comp = -1

    def setParentID(self, id):
        self.pID = id

    def selectVariable(self, type, name, index):
        self.type = type
        self.vName = name
        self.comp = index

    def setColor(self, r, g, b):
        self.red = r
        self.green = g
        self.blue = b

    def useVariable(self):
        self.isVariable = True

    def appendBlock(self, pID, index):
        self.blocks.setdefault(pID, set()).add(index)

    def updateColor(self):
        pidList = self.blocks.keys()
        sblock = ""
        for parent in pidList:
            strBlock = ""
            blockList = self.blocks.get(parent)
            for blockID in blockList:
                strBlock = strBlock + str(blockID) + ","
            strBlock = str(parent) + ":" + strBlock[:-1]
            sblock = sblock + strBlock + ';'
        sblock = sblock[:-1]
        blockStr = bytes(sblock, encoding='utf-8')

        sname = bytes(self.vName, encoding='utf-8')
        process.setBlockColor(blockStr, sname, c_int(self.type), c_int(self.comp), c_double(self.red),
                              c_double(self.green), c_double(self.blue), c_bool(self.isVariable))
        del self

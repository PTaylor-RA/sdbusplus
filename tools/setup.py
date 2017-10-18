from distutils.core import setup
from distutils.command.build import build
from distutils.dir_util import copy_tree


class CustomBuild(build):
    def run(self):
        if ('..' != '..'):
            copy_tree('../tools/', '../tools/', update=1)

setup(name='sdbusplus',
      version='1.0',
      package_dir={'':'../tools'},
      packages=['sdbusplus'],
      scripts=['../tools/sdbus++'],
      cmdclass={'build': CustomBuild},
      package_data={'sdbusplus': ['templates/*.mako.*']},
      )

node 'default'
{
}
node 'sbob12'
{
#
  exec
  { 'groupadd':
     command => '/usr/sbin/groupadd -g 2357 bobs',
     unless  => '/bin/cat /etc/group | /bin/grep bobs',
  }
#
  exec
  { 'mkdir_home_bobs':
     command => '/bin/mkdir /home/bobs',
     unless  => '/bin/ls /home | /bin/grep bobs',
  }
#
  exec
  { 'mkdir_home_bobs_local_hooks':
     command => '/bin/mkdir -p /home/bobs/local/hooks',
     unless  => '/bin/ls /home/bobs/local | /bin/grep hooks',
  }
#
  user
  { 'bobs':
     ensure   => present,
     uid      => '2357',
     gid      => '2357',
     shell    => '/bin/bash',
     home     => '/home/bobs',
     password =>  generate('/usr/bin/perl', '-e', "print crypt(\"u1xu2xsu3\", \"salt\")"),
  }
#
  exec
  { 'chown':
     command => '/bin/chown -R bobs /home/bobs',
  }
#
  exec
  { 'chgrp':
     command => '/bin/chgrp -R bobs /home/bobs',
  }
#
#
  file
  { '/home/bobs/local/hooks/hook_script.sh': # Resource type file
    ensure  => 'present', # make sure it exists
    owner   => 'bobs', # Ownership
    group   => 'bobs', # Group Name
    mode    => '0755', # Directory permissions
    content => "#!/bin/bash \n pushd /home/bobs > /dev/null \n /bin/rm -rf BOBsSPH \n git clone git@github.com:djb158/BOBsSPH.git \n popd > /dev/null \n sleep 1 \n pushd /home/bobs/BOBsSPH > /dev/null \n ./sph_config_make \n popd > /dev/null"
  }
# execute 'apt-get update'
  exec
  { 'apt-update':                         # exec resource named 'apt-update'
    command => '/usr/bin/apt-get update'  # command this resource will run
  }
#
  package
  {'autotools-dev':
    require => Exec['apt-update'],        # require 'apt-update' before installing
    ensure => installed,
  }
  package
  {'automake':
    require => Exec['apt-update'],        # require 'apt-update' before installing
    ensure => installed,
  }
#
# install libpthread package
  package
  {'libpthread-stubs0-dev':
    require => Exec['apt-update'],        # require 'apt-update' before installing
    ensure => installed,
  }
#
# install git package
  package
  {'git':
    require => Exec['apt-update'],        # require 'apt-update' before installing
    ensure => installed,
  }
#
# install openmpi-bin package
  package
  {'openmpi-bin':
    require => Exec['apt-update'],        # require 'apt-update' before installing
    ensure  => installed,
  }
#
# install valgrind package
  package
  {'valgrind':
    require => Exec['apt-update'],        # require 'apt-update' before installing
    ensure  => installed,
  }
#
# install mcollective package
  package
  {'mcollective':
    require => Exec['apt-update'],        # require 'apt-update' before installing
    ensure  => installed,
  }
#
# install mcollective-common package
  package
  {'mcollective-common':
    require => Exec['apt-update'],        # require 'apt-update' before installing
    ensure  => installed,
  }
#
# install tofrodos
  package
  {'tofrodos':
    require => Exec['apt-update'],        # require 'apt-update' before installing
    ensure  => installed,
  }
#
  exec
  { 'wget_ann':
     command => '/usr/bin/wget -P /usr/local https://www.cs.umd.edu/~mount/ANN/Files/1.1.2/ann_1.1.2.tar.gz;/bin/tar -zxvf /usr/local/ann_1.1.2.tar.gz;
                 /bin/echo -e "mpi-mpic++:
\t\$(MAKE) targets \"ANNLIB = libANN.a\" \"C++ = mpic++\" \"CFLAGS = -O3 -ggdb\" \"MAKELIB = ar ruv\" \"RANLIB = true\"" >> /usr/local/ann_1.1.2/Make-config;
                  /bin/sed -i -e \'s/authors-debug authors-perf/authors-debug authors-perf mpi-mpic++/g\' /usr/local/ann_1.1.2/Makefile;
                  cd /usr/local/ann_1.1.2;
                  /usr/bin/make mpi-mpic++',
     unless  => '/bin/ls /usr/local | /bin/grep ann_1.1.2',
  }
}

#!/bin/bash
download_boost() {
    boost_version=$1
    shift
    boost_sha256=$1
    shift
    boost_version_underscore=$(echo $boost_version | sed 's/\./_/g')
    boost_fname=boost_${boost_version_underscore}.tar.bz2
    set +e
    while true; do
        url_base=$1
        shift
        if [ -z $url_base ]; then
            echo "Error: failed to download boost."
            exit
        fi
        url=$url_base/$boost_fname
        wget -c --no-verbose -O $boost_fname $url
        if [ $? != 0 -o ! -e $boost_fname ]; then
            echo "Download of $url failed"
        elif [ $(sha256sum $boost_fname | awk '{print $1}') != $boost_sha256 ]; then
            echo "Error: failed to download boost: SHA256 mismatch."
        else
            break
        fi
    done
    set -e
    tar xjf $boost_fname -C src \
        --exclude="$boost_version_underscore/libs/*/doc" \
        --exclude="$boost_version_underscore/libs/*/example" \
        --exclude="$boost_version_underscore/libs/*/examples" \
        --exclude="$boost_version_underscore/libs/*/meta" \
        --exclude="$boost_version_underscore/libs/*/test" \
        --exclude="$boost_version_underscore/tools/boostbook" \
        --exclude="$boost_version_underscore/tools/quickbook" \
        --exclude="$boost_version_underscore/tools/auto_index" \
        --exclude='doc' --exclude='more' --exclude='status'
    mv src/boost_${boost_version_underscore} src/boost
    #tar cf ${outfile}.boost.tar ${outfile}/src/boost
    #rm -rf src/boost
}


#version=$1
#[ -z "$version" ] && version=`git describe --match 'v*' | sed 's/^v//'`
month=$(date +%Y%m%d)
commit_id=$(git --git-dir=${repo_alias_name}/.git rev-parse --short HEAD)
version="${commit_id}.${month}"
outfile="gitsubmodule-$version"

boost_version=1.72.0
download_boost $boost_version 59c9b274bc451cf91a9ba1dd2c7fdcaf5d60b1b3aa83f2c9fa143417cc660722 \
               http://10.127.10.200:60030/fitstor/auto-backup/ceph/builddep \
               https://downloads.sourceforge.net/project/boost/boost/$boost_version \
               https://download.ceph.com/qa

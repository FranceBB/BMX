#!/bin/sh

MD5TOOL=../file_md5


BASE_COMMAND="../../apps/raw2bmx/raw2bmx --regtest -t avid -o /tmp/avidmxftest -y 10:11:12:13 --clip test --tape testtape "
if [ "$4" != "" ]; then
  BASE_COMMAND="$BASE_COMMAND -f $4 "
fi
if [ "$3" = "unc" ]; then
  BASE_COMMAND="$BASE_COMMAND --height 576 "
fi


# create essence data
../create_test_essence -t 1 -d $1 /tmp/pcm.raw
../create_test_essence -t $2 -d $1 /tmp/test_in.raw

# write
$BASE_COMMAND -a 16:9 --$3 /tmp/test_in.raw -q 16 --locked true --pcm /tmp/pcm.raw -q 16 --locked true --pcm /tmp/pcm.raw >/dev/null

# calculate md5sum and compare with expected value
$MD5TOOL < /tmp/avidmxftest_v1.mxf > /tmp/test.md5s
$MD5TOOL < /tmp/avidmxftest_a1.mxf >> /tmp/test.md5s
$MD5TOOL < /tmp/avidmxftest_a2.mxf >> /tmp/test.md5s
if diff /tmp/test.md5s ${srcdir}/$3$4.md5s
then
	RESULT=0
else
	echo "*** ERROR: $3$4 regression"
	RESULT=1
fi

# clean-up
rm -Rf /tmp/pcm.raw /tmp/test_in.raw /tmp/avidmxftest_v1.mxf /tmp/avidmxftest_a1.mxf /tmp/avidmxftest_a2.mxf /tmp/test.md5s


exit $RESULT

<?php

$DB_HOST = "165.132.121.124";
// 데이터베이스 주소
$DB_NAME = "master";
// 데이터베이스 이름
$DB_USER = "root";
// 데이터베이스 사용자
$DB_PASS = "0000";
// 데이터베이스 비밀번호
$conn = mysqli_connect($DB_HOST, $DB_USER, $DB_PASS, $DB_NAME);

if (!$conn) {
    die("DB Connection Error: " . mysqli_error($conn));
}

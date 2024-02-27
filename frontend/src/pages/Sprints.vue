<template>
  <div class="back">
    <div class="profile">
      <div class="info">

      </div>
      <div class="body">

      </div>
    </div>
  </div>
</template>

<script>
export default {

}
</script>

<style scoped>
@import "@/styles.css";


hr {
  margin-top: 5px;
  background-color: var(--border-light-gray-color);
  padding: .3px;
  border: var(--border-light-gray-color);
}

.back {
  /* background-color: #0d1117; */
  background-color: var(--background-app-color);
  position: fixed;
  width: 100vw;
  max-height: 100vh;
  height: 100vh;
  padding: 80px 5% 24px 5%;
  overflow-y: auto;
  overflow-x: hidden;

}

.profile {
  position: absolute;
  border: 1px solid red;
  width: 85vw;
  height: 100%;
}

.info {
  position: absolute;
  top: 0;
  left: 0;
  border: 1px solid #31a0a8;
  width: 25%;
  height: 80vh;
  padding: 2%;
}

.body {
  position: absolute;
  top: 0;
  left: 25%;
  border: 1px solid #cfcfcf;
  width: 75%;
  height: 80vh;
  padding: 0 10px 10px 10px;
}
</style>